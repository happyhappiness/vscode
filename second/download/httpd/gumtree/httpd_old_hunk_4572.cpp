    ap_assert(stream);
    if (stream->out_buffer) {
        /* remove any left over output buckets that may still have
         * references into request pools */
        apr_brigade_cleanup(stream->out_buffer);
    }
    h2_beam_abort(stream->input);
    status = h2_beam_wait_empty(stream->input, APR_NONBLOCK_READ);
    if (status == APR_EAGAIN) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                      "h2_stream(%ld-%d): wait on input drain", 
                      stream->session->id, stream->id);
        status = h2_beam_wait_empty(stream->input, APR_BLOCK_READ);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                      "h2_stream(%ld-%d): input drain returned", 
                      stream->session->id, stream->id);
    }
}

void h2_stream_destroy(h2_stream *stream)
{
    ap_assert(stream);
    ap_assert(!h2_mplx_stream_get(stream->session->mplx, stream->id));
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                  "h2_stream(%ld-%d): destroy", 
                  stream->session->id, stream->id);
    stream->can_be_cleaned = 1;
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
}

void h2_stream_eos_destroy(h2_stream *stream)
{
    h2_session_stream_done(stream->session, stream);
    /* stream possibly destroyed */
}

apr_pool_t *h2_stream_detach_pool(h2_stream *stream)
{
    apr_pool_t *pool = stream->pool;
    stream->pool = NULL;
    return pool;
}

void h2_stream_rst(h2_stream *stream, int error_code)
{
    stream->rst_error = error_code;
    close_input(stream);
    close_output(stream);
    if (stream->out_buffer) {
        apr_brigade_cleanup(stream->out_buffer);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): reset, error=%d", 
                  stream->session->id, stream->id, error_code);
}

apr_status_t h2_stream_set_request_rec(h2_stream *stream, request_rec *r)
{
    h2_request *req;
    apr_status_t status;

    ap_assert(stream->request == NULL);
    ap_assert(stream->rtmp == NULL);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    status = h2_request_rcreate(&req, stream->pool, r);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): set_request_rec %s host=%s://%s%s",
                  stream->id, req->method, req->scheme, req->authority, 
                  req->path);
    stream->rtmp = req;
    return status;
}

apr_status_t h2_stream_set_request(h2_stream *stream, const h2_request *r)
{
    ap_assert(stream->request == NULL);
    ap_assert(stream->rtmp == NULL);
    stream->rtmp = h2_request_clone(stream->pool, r);
    return APR_SUCCESS;
}

static apr_status_t add_trailer(h2_stream *stream,
                                const char *name, size_t nlen,
                                const char *value, size_t vlen)
{
    conn_rec *c = stream->session->c;
    char *hname, *hvalue;

    if (nlen == 0 || name[0] == ':') {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, c, APLOGNO(03060)
                      "h2_request(%ld-%d): pseudo header in trailer",
                      c->id, stream->id);
        return APR_EINVAL;
    }
    if (h2_req_ignore_trailer(name, nlen)) {
        return APR_SUCCESS;
    }
    if (!stream->trailers) {
