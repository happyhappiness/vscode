static int on_data_chunk_recv(nghttp2_session *ngh2, uint8_t flags,
                              int32_t stream_id, const uint8_t *data,
                              size_t len, void *user_data) 
{
    h2_proxy_session *session = user_data;
    h2_proxy_stream *stream;
    apr_bucket *b;
    apr_status_t status;
    
    stream = nghttp2_session_get_stream_user_data(ngh2, stream_id);
    if (!stream) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(03358)
                     "h2_proxy_session(%s): recv data chunk for "
                     "unknown stream %d, ignored", 
                     session->id, stream_id);
        return 0;
    }
    
    if (!stream->data_received) {
        /* last chance to manipulate response headers.
         * after this, only trailers */
        h2_proxy_stream_end_headers_out(stream);
        stream->data_received = 1;
    }
    
    b = apr_bucket_transient_create((const char*)data, len, 
                                    stream->r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(stream->output, b);
    /* always flush after a DATA frame, as we have no other indication
     * of buffer use */
    b = apr_bucket_flush_create(stream->r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(stream->output, b);
    
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, stream->r, APLOGNO(03359)
                  "h2_proxy_session(%s): pass response data for "
                  "stream %d, %d bytes", session->id, stream_id, (int)len);
    status = ap_pass_brigade(stream->r->output_filters, stream->output);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, APLOGNO(03344)
                      "h2_proxy_session(%s): passing output on stream %d", 
                      session->id, stream->id);
        nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE,
                                  stream_id, NGHTTP2_STREAM_CLOSED);
        return NGHTTP2_ERR_STREAM_CLOSING;
    }
    if (stream->standalone) {
        nghttp2_session_consume(ngh2, stream_id, len);
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, stream->r,
                      "h2_proxy_session(%s): stream %d, win_update %d bytes",
                      session->id, stream_id, (int)len);
    }
    return 0;
}