                          APLOGNO(02932) "nghttp2_session_upgrade: %s", 
                          nghttp2_strerror(*rv));
            return status;
        }
        
        /* Now we need to auto-open stream 1 for the request we got. */
        stream = h2_session_open_stream(session, 1);
        if (!stream) {
            status = APR_EGENERAL;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, session->r,
                          APLOGNO(02933) "open stream 1: %s", 
                          nghttp2_strerror(*rv));
            return status;
        }
        
        status = h2_stream_set_request(stream, session->r);
        if (status != APR_SUCCESS) {
            return status;
        }
        status = stream_schedule(session, stream, 1);
        if (status != APR_SUCCESS) {
            return status;
        }
    }

    slen = 0;
    settings[slen].settings_id = NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS;
    settings[slen].value = (uint32_t)session->max_stream_count;
    ++slen;
    win_size = h2_config_geti(session->config, H2_CONF_WIN_SIZE);
    if (win_size != H2_INITIAL_WINDOW_SIZE) {
        settings[slen].settings_id = NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE;
        settings[slen].value = win_size;
        ++slen;
    }
    
    *rv = nghttp2_submit_settings(session->ngh2, NGHTTP2_FLAG_NONE,
                                  settings, slen);
    if (*rv != 0) {
        status = APR_EGENERAL;
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02935) "nghttp2_submit_settings: %s", 
                      nghttp2_strerror(*rv));
    }
    else {
        /* use maximum possible value for connection window size. We are only
         * interested in per stream flow control. which have the initial window
         * size configured above.
         * Therefore, for our use, the connection window can only get in the
         * way. Example: if we allow 100 streams with a 32KB window each, we
         * buffer up to 3.2 MB of data. Unless we do separate connection window
         * interim updates, any smaller connection window will lead to blocking
         * in DATA flow.
         */
        *rv = nghttp2_submit_window_update(session->ngh2, NGHTTP2_FLAG_NONE,
                                           0, NGHTTP2_MAX_WINDOW_SIZE - win_size);
        if (*rv != 0) {
            status = APR_EGENERAL;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          APLOGNO(02970) "nghttp2_submit_window_update: %s", 
                          nghttp2_strerror(*rv));        
        }
    }
    return status;
}

typedef struct {
    h2_session *session;
    int resume_count;
} resume_ctx;

static int resume_on_data(void *ctx, h2_stream *stream) {
    resume_ctx *rctx = (resume_ctx*)ctx;
    h2_session *session = rctx->session;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    
    if (h2_stream_is_suspended(stream)) {
        if (h2_mplx_out_has_data_for(stream->session->mplx, stream->id)) {
            int rv;
            h2_stream_set_suspended(stream, 0);
            ++rctx->resume_count;
            
            rv = nghttp2_session_resume_data(session->ngh2, stream->id);
            ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
