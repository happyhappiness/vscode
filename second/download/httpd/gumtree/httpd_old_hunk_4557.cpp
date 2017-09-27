{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;

    ap_assert(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_stream(%ld-%d): on_headers", session->id, stream->id);
    if (headers->status < 100) {
        int err = H2_STREAM_RST(stream, headers->status);
        rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                       stream->id, err);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                  "h2_stream(%ld-%d): unpexected header status %d, stream rst", 
                  session->id, stream->id, headers->status);
        goto leave;
    }
    else if (stream->has_response) {
        h2_ngheader *nh;
        
        nh = h2_util_ngheader_make(stream->pool, headers->headers);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03072)
                      "h2_stream(%ld-%d): submit %d trailers",
                      session->id, (int)stream->id,(int) nh->nvlen);
        rv = nghttp2_submit_trailer(session->ngh2, stream->id, nh->nv, nh->nvlen);
        goto leave;
    }
    else {
        nghttp2_data_provider provider, *pprovider = NULL;
        h2_ngheader *ngh;
        apr_table_t *hout;
        const char *note;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03073)
                      "h2_stream(%ld-%d): submit response %d, REMOTE_WINDOW_SIZE=%u",
                      session->id, stream->id, headers->status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));
        
        if (!eos || len > 0) {
            memset(&provider, 0, sizeof(provider));
            provider.source.fd = stream->id;
            provider.read_callback = stream_data_cb;
