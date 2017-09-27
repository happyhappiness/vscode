
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
        stream->trailers = apr_table_make(stream->pool, 5);
    }
    hname = apr_pstrndup(stream->pool, name, nlen);
    hvalue = apr_pstrndup(stream->pool, value, vlen);
    h2_util_camel_case_header(hname, nlen);
    apr_table_mergen(stream->trailers, hname, hvalue);
    
    return APR_SUCCESS;
}

apr_status_t h2_stream_add_header(h2_stream *stream,
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    int error = 0;
    ap_assert(stream);
    
    if (stream->has_response) {
        return APR_EINVAL;    
    }
    ++stream->request_headers_added;
    if (name[0] == ':') {
        if ((vlen) > stream->session->s->limit_req_line) {
            /* pseudo header: approximation of request line size check */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                          "h2_stream(%ld-%d): pseudo header %s too long", 
                          stream->session->id, stream->id, name);
            error = HTTP_REQUEST_URI_TOO_LARGE;
        }
    }
    else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
        /* header too long */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): header %s too long", 
                      stream->session->id, stream->id, name);
        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
    }
    
    if (stream->request_headers_added 
        > stream->session->s->limit_req_fields + 4) {
        /* too many header lines, include 4 pseudo headers */
        if (stream->request_headers_added 
            > stream->session->s->limit_req_fields + 4 + 100) {
            /* yeah, right */
            return APR_ECONNRESET;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): too many header lines", 
                      stream->session->id, stream->id);
        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
    }
    
    if (h2_stream_is_scheduled(stream)) {
        return add_trailer(stream, name, nlen, value, vlen);
    }
    else if (error) {
        return h2_stream_set_error(stream, error); 
    }
    else {
        if (!stream->rtmp) {
            stream->rtmp = h2_req_create(stream->id, stream->pool, 
                                         NULL, NULL, NULL, NULL, NULL, 0);
        }
        if (stream->state != H2_STREAM_ST_OPEN) {
            return APR_ECONNRESET;
        }
        return h2_request_add_header(stream->rtmp, stream->pool,
                                     name, nlen, value, vlen);
    }
}

apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
                                h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status = APR_EINVAL;
    ap_assert(stream);
    ap_assert(stream->session);
    ap_assert(stream->session->mplx);
    
    if (!stream->scheduled) {
        if (eos) {
            close_input(stream);
        }

        if (h2_stream_is_ready(stream)) {
            /* already have a resonse, probably a HTTP error code */
            return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
        }
        else if (!stream->request && stream->rtmp) {
            /* This is the common case: a h2_request was being assembled, now
             * it gets finalized and checked for completness */
            status = h2_request_end_headers(stream->rtmp, stream->pool, eos);
            if (status == APR_SUCCESS) {
                stream->rtmp->serialize = h2_config_geti(stream->session->config,
                                                         H2_CONF_SER_HEADERS); 

                stream->request = stream->rtmp;
                stream->rtmp = NULL;
                stream->scheduled = 1;
                
                stream->push_policy = h2_push_policy_determine(stream->request->headers, 
                                                               stream->pool, push_enabled);
            
                
                status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): scheduled %s %s://%s%s "
                              "chunked=%d",
                              stream->session->id, stream->id,
                              stream->request->method, stream->request->scheme,
                              stream->request->authority, stream->request->path,
                              stream->request->chunked);
                return status;
            }
        }
        else {
            status = APR_ECONNRESET;
        }
    }
    
    h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                  stream->session->id, stream->id,
                  stream->request->method, stream->request->scheme,
                  stream->request->authority, stream->request->path);
    return status;
}

int h2_stream_is_scheduled(const h2_stream *stream)
{
    return stream->scheduled;
}

apr_status_t h2_stream_close_input(h2_stream *stream)
{
    conn_rec *c = stream->session->c;
    apr_status_t status;
    apr_bucket_brigade *tmp;
    apr_bucket *b;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->session->id, stream->id);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    if (stream->trailers && !apr_is_empty_table(stream->trailers)) {
        h2_headers *r = h2_headers_create(HTTP_OK, stream->trailers, 
                                          NULL, stream->pool);
        b = h2_bucket_headers_create(c->bucket_alloc, r);
        APR_BRIGADE_INSERT_TAIL(tmp, b);
        stream->trailers = NULL;
    }
    
    b = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmp, b);
    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
    apr_brigade_destroy(tmp);
    return status;
}

apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len, int eos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    apr_bucket_brigade *tmp;
    
    ap_assert(stream);
    if (!stream->input) {
        return APR_EOF;
    }
    if (input_closed(stream) || !stream->request) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request != NULL);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);
    
    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    apr_brigade_write(tmp, NULL, NULL, data, len);
    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
    apr_brigade_destroy(tmp);
    
    stream->in_data_frames++;
    stream->in_data_octets += len;
    
    if (eos) {
        return h2_stream_close_input(stream);
    }
    
    return status;
}

static apr_status_t fill_buffer(h2_stream *stream, apr_size_t amount)
{
    conn_rec *c = stream->session->c;
    apr_bucket *b;
    apr_status_t status;
    
    if (!stream->output) {
        return APR_EOF;
    }
    status = h2_beam_receive(stream->output, stream->out_buffer, 
                             APR_NONBLOCK_READ, amount);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c,
                  "h2_stream(%ld-%d): beam_received",
                  stream->session->id, stream->id);
    /* The buckets we reveive are using the stream->out_buffer pool as
     * lifetime which is exactly what we want since this is stream->pool.
     *
     * However: when we send these buckets down the core output filters, the
     * filter might decide to setaside them into a pool of its own. And it
     * might decide, after having sent the buckets, to clear its pool.
     *
     * This is problematic for file buckets because it then closed the contained
     * file. Any split off buckets we sent afterwards will result in a 
     * APR_EBADF.
     */
    for (b = APR_BRIGADE_FIRST(stream->out_buffer);
         b != APR_BRIGADE_SENTINEL(stream->out_buffer);
         b = APR_BUCKET_NEXT(b)) {
        if (APR_BUCKET_IS_FILE(b)) {
            apr_bucket_file *f = (apr_bucket_file *)b->data;
            apr_pool_t *fpool = apr_file_pool_get(f->fd);
            if (fpool != c->pool) {
                apr_bucket_setaside(b, c->pool);
