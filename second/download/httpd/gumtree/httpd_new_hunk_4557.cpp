{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;

    ap_assert(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  H2_STRM_MSG(stream, "on_headers"));
    if (headers->status < 100) {
        h2_stream_rst(stream, headers->status);
        goto leave;
    }
    else if (stream->has_response) {
        h2_ngheader *nh;
        
        status = h2_res_create_ngtrailer(&nh, stream->pool, headers);
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                      H2_STRM_LOG(APLOGNO(03072), stream, "submit %d trailers"), 
                      (int)nh->nvlen);
        if (status == APR_SUCCESS) {
            rv = nghttp2_submit_trailer(session->ngh2, stream->id, 
                                        nh->nv, nh->nvlen);
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          H2_STRM_LOG(APLOGNO(10024), stream, "invalid trailers"));
            h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
        }
        goto leave;
    }
    else {
        nghttp2_data_provider provider, *pprovider = NULL;
        h2_ngheader *ngh;
        const char *note;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_STRM_LOG(APLOGNO(03073), stream, "submit response %d, REMOTE_WINDOW_SIZE=%u"),
                      headers->status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));
        
        if (!eos || len > 0) {
            memset(&provider, 0, sizeof(provider));
            provider.source.fd = stream->id;
            provider.read_callback = stream_data_cb;
