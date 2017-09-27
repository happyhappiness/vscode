    ap_assert(stream);
    if (stream->out_buffer) {
        /* remove any left over output buckets that may still have
         * references into request pools */
        apr_brigade_cleanup(stream->out_buffer);
    }
    if (stream->input) {
        h2_beam_abort(stream->input);
        status = h2_beam_wait_empty(stream->input, APR_NONBLOCK_READ);
        if (status == APR_EAGAIN) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                          H2_STRM_MSG(stream, "wait on input drain"));
            status = h2_beam_wait_empty(stream->input, APR_BLOCK_READ);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                          H2_STRM_MSG(stream, "input drain returned"));
        }
    }
}

void h2_stream_destroy(h2_stream *stream)
{
    ap_assert(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                  H2_STRM_MSG(stream, "destroy"));
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
        stream->pool = NULL;
    }
}

apr_pool_t *h2_stream_detach_pool(h2_stream *stream)
{
    apr_pool_t *pool = stream->pool;
    stream->pool = NULL;
    return pool;
}

apr_status_t h2_stream_prep_processing(h2_stream *stream)
{
    if (stream->request) {
        const h2_request *r = stream->request;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      H2_STRM_MSG(stream, "schedule %s %s://%s%s chunked=%d"),
                      r->method, r->scheme, r->authority, r->path, r->chunked);
        setup_input(stream);
        stream->scheduled = 1;
        return APR_SUCCESS;
    }
    return APR_EINVAL;
}

void h2_stream_rst(h2_stream *stream, int error_code)
{
    stream->rst_error = error_code;
    if (stream->input) {
        h2_beam_abort(stream->input);
    }
    if (stream->output) {
        h2_beam_leave(stream->output);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  H2_STRM_MSG(stream, "reset, error=%d"), error_code);
    h2_stream_dispatch(stream, H2_SEV_CANCELLED);
}

apr_status_t h2_stream_set_request_rec(h2_stream *stream, 
                                       request_rec *r, int eos)
{
    h2_request *req;
    apr_status_t status;

    ap_assert(stream->request == NULL);
    ap_assert(stream->rtmp == NULL);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    status = h2_request_rcreate(&req, stream->pool, r);
    if (status == APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, 
                      H2_STRM_LOG(APLOGNO(03058), stream, 
                      "set_request_rec %s host=%s://%s%s"),
                      req->method, req->scheme, req->authority, req->path);
        stream->rtmp = req;
        /* simulate the frames that led to this */
        return h2_stream_recv_frame(stream, NGHTTP2_HEADERS, 
                                    NGHTTP2_FLAG_END_STREAM);
    }
    return status;
}

void h2_stream_set_request(h2_stream *stream, const h2_request *r)
{
    ap_assert(stream->request == NULL);
    ap_assert(stream->rtmp == NULL);
    stream->rtmp = h2_request_clone(stream->pool, r);
}

static void set_error_response(h2_stream *stream, int http_status)
{
    if (!h2_stream_is_ready(stream)) {
        conn_rec *c = stream->session->c;
        apr_bucket *b;
        h2_headers *response;
        
        response = h2_headers_die(http_status, stream->request, stream->pool);
        prep_output(stream);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
        b = h2_bucket_headers_create(c->bucket_alloc, response);
        APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
    }
}

static apr_status_t add_trailer(h2_stream *stream,
                                const char *name, size_t nlen,
                                const char *value, size_t vlen)
{
    conn_rec *c = stream->session->c;
    char *hname, *hvalue;

    if (nlen == 0 || name[0] == ':') {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, c, 
                      H2_STRM_LOG(APLOGNO(03060), stream, 
                      "pseudo header in trailer"));
        return APR_EINVAL;
    }
    if (h2_req_ignore_trailer(name, nlen)) {
        return APR_SUCCESS;
    }
    if (!stream->trailers) {
