static ssize_t stream_data_cb(nghttp2_session *ng2s,
                              int32_t stream_id,
                              uint8_t *buf,
                              size_t length,
                              uint32_t *data_flags,
                              nghttp2_data_source *source,
                              void *puser)
{
    h2_session *session = (h2_session *)puser;
    apr_off_t nread = length;
    int eos = 0;
    apr_status_t status;
    h2_stream *stream;
    AP_DEBUG_ASSERT(session);
    
    /* The session wants to send more DATA for the stream. We need
     * to find out how much of the requested length we can send without
     * blocking.
     * Indicate EOS when we encounter it or DEFERRED if the stream
     * should be suspended.
     * TODO: for handling of TRAILERS,  the EOF indication needs
     * to be aware of that.
     */
 
    (void)ng2s;
    (void)buf;
    (void)source;
    stream = h2_session_get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02937) 
                      "h2_stream(%ld-%d): data requested but stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    AP_DEBUG_ASSERT(!h2_stream_is_suspended(stream));
    
    status = h2_stream_prep_read(stream, &nread, &eos);
    if (nread) {
        *data_flags |=  NGHTTP2_DATA_FLAG_NO_COPY;
    }
    
    switch (status) {
        case APR_SUCCESS:
            break;
            
        case APR_ECONNRESET:
            return nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                stream->id, stream->rst_error);
            
        case APR_EAGAIN:
            /* If there is no data available, our session will automatically
             * suspend this stream and not ask for more data until we resume
             * it. Remember at our h2_stream that we need to do this.
             */
            nread = 0;
            h2_stream_set_suspended(stream, 1);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_stream(%ld-%d): suspending stream",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_DEFERRED;
            
        case APR_EOF:
            nread = 0;
            eos = 1;
            break;
            
        default:
            nread = 0;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (eos) {
        apr_table_t *trailers = h2_stream_get_trailers(stream);
        if (trailers && !apr_is_empty_table(trailers)) {
            h2_ngheader *nh;
            int rv;
            
            nh = h2_util_ngheader_make(stream->pool, trailers);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_stream(%ld-%d): submit %d trailers",
                          session->id, (int)stream_id,(int) nh->nvlen);
            rv = nghttp2_submit_trailer(ng2s, stream->id, nh->nv, nh->nvlen);
            if (rv < 0) {
                nread = rv;
            }
            *data_flags |= NGHTTP2_DATA_FLAG_NO_END_STREAM;
        }
        
        *data_flags |= NGHTTP2_DATA_FLAG_EOF;
    }
    
    return (ssize_t)nread;
}