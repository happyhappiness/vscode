
void h2_stream_rst(h2_stream *stream, int error_code)
{
    stream->rst_error = error_code;
    close_input(stream);
    close_output(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): reset, error=%d", 
                  stream->session->id, stream->id, error_code);
}

struct h2_response *h2_stream_get_response(h2_stream *stream)
{
    return stream->response;
}

apr_status_t h2_stream_set_request(h2_stream *stream, request_rec *r)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    set_state(stream, H2_STREAM_ST_OPEN);
    status = h2_request_rwrite(stream->request, stream->pool, r);
    stream->request->serialize = h2_config_geti(h2_config_rget(r), 
                                                H2_CONF_SER_HEADERS);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  stream->request->id, stream->request->method, 
                  stream->request->scheme, stream->request->authority, 
                  stream->request->path);

    return status;
}

apr_status_t h2_stream_add_header(h2_stream *stream,
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    AP_DEBUG_ASSERT(stream);
    if (!stream->response) {
        if (name[0] == ':') {
            if ((vlen) > stream->session->s->limit_req_line) {
                /* pseudo header: approximation of request line size check */
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): pseudo header %s too long", 
                              stream->session->id, stream->id, name);
                return h2_stream_set_error(stream, 
                                           HTTP_REQUEST_URI_TOO_LARGE);
            }
        }
        else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
            /* header too long */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                          "h2_stream(%ld-%d): header %s too long", 
                          stream->session->id, stream->id, name);
            return h2_stream_set_error(stream, 
                                       HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
        }
        
        if (name[0] != ':') {
            ++stream->request_headers_added;
            if (stream->request_headers_added 
                > stream->session->s->limit_req_fields) {
                /* too many header lines */
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): too many header lines", 
                              stream->session->id, stream->id);
                return h2_stream_set_error(stream, 
                                           HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
            }
        }
    }
    
    if (h2_stream_is_scheduled(stream)) {
        return h2_request_add_trailer(stream->request, stream->pool,
                                      name, nlen, value, vlen);
    }
    else {
        if (!input_open(stream)) {
            return APR_ECONNRESET;
        }
        return h2_request_add_header(stream->request, stream->pool,
                                     name, nlen, value, vlen);
    }
}

apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
                                h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(stream->session);
    AP_DEBUG_ASSERT(stream->session->mplx);
    
    if (!output_open(stream)) {
        return APR_ECONNRESET;
    }
    if (stream->scheduled) {
        return APR_EINVAL;
    }
    if (eos) {
        close_input(stream);
    }
    
    if (stream->response) {
        /* already have a resonse, probably a HTTP error code */
        return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
    }
    
    /* Seeing the end-of-headers, we have everything we need to 
     * start processing it.
     */
    status = h2_request_end_headers(stream->request, stream->pool, 
                                    eos, push_enabled);
    if (status == APR_SUCCESS) {
        stream->request->body = !eos;
        stream->scheduled = 1;
        stream->input_remaining = stream->request->content_length;
        
        status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    else {
        h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                      "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    
    return status;
}

int h2_stream_is_scheduled(const h2_stream *stream)
{
    return stream->scheduled;
}

apr_status_t h2_stream_close_input(h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->session->id, stream->id);
                  
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    if (close_input(stream) && stream->input) {
        status = h2_beam_close(stream->input);
    }
    return status;
}

apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len, int eos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    if (!stream->input) {
        return APR_EOF;
    }
    if (input_closed(stream) || !stream->request->eoh) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request->eoh);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);

    if (!stream->request->chunked) {
        stream->input_remaining -= len;
        if (stream->input_remaining < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                          APLOGNO(02961) 
                          "h2_stream(%ld-%d): got %ld more content bytes than announced "
                          "in content-length header: %ld", 
                          stream->session->id, stream->id,
                          (long)stream->request->content_length, 
                          -(long)stream->input_remaining);
            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
            return APR_ECONNABORTED;
        }
    }
    
    if (!stream->tmp) {
        stream->tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    }
    apr_brigade_write(stream->tmp, NULL, NULL, data, len);
    if (eos) {
        APR_BRIGADE_INSERT_TAIL(stream->tmp, 
                                apr_bucket_eos_create(c->bucket_alloc)); 
        close_input(stream);
    }
    
    status = h2_beam_send(stream->input, stream->tmp, APR_BLOCK_READ);
    apr_brigade_cleanup(stream->tmp);
    return status;
}

void h2_stream_set_suspended(h2_stream *stream, int suspended)
{
    AP_DEBUG_ASSERT(stream);
    stream->suspended = !!suspended;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
                  "h2_stream(%ld-%d): suspended=%d",
                  stream->session->id, stream->id, stream->suspended);
}

int h2_stream_is_suspended(const h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    return stream->suspended;
}

static apr_status_t fill_buffer(h2_stream *stream, apr_size_t amount)
{
    conn_rec *c = stream->session->c;
    apr_bucket *b;
    apr_status_t status;
    
    if (!stream->output) {
        return APR_EOF;
    }
    status = h2_beam_receive(stream->output, stream->buffer, 
                             APR_NONBLOCK_READ, amount);
    /* The buckets we reveive are using the stream->buffer pool as
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
    for (b = APR_BRIGADE_FIRST(stream->buffer);
         b != APR_BRIGADE_SENTINEL(stream->buffer);
         b = APR_BUCKET_NEXT(b)) {
        if (APR_BUCKET_IS_FILE(b)) {
            apr_bucket_file *f = (apr_bucket_file *)b->data;
            apr_pool_t *fpool = apr_file_pool_get(f->fd);
            if (fpool != c->pool) {
                apr_bucket_setaside(b, c->pool);
