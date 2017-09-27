                          APLOGNO(02932) "nghttp2_session_upgrade: %s", 
                          nghttp2_strerror(*rv));
            return status;
        }
        
        /* Now we need to auto-open stream 1 for the request we got. */
        *rv = stream_open(session, 1);
        if (*rv != 0) {
            status = APR_EGENERAL;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, session->r,
                          APLOGNO(02933) "open stream 1: %s", 
                          nghttp2_strerror(*rv));
            return status;
        }
        
        stream = h2_stream_set_get(session->streams, 1);
        if (stream == NULL) {
            status = APR_EGENERAL;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, session->r,
                          APLOGNO(02934) "lookup of stream 1");
            return status;
        }
        
        status = h2_stream_rwrite(stream, session->r);
        if (status != APR_SUCCESS) {
            return status;
        }
        status = stream_end_headers(session, stream, 1);
        if (status != APR_SUCCESS) {
            return status;
        }
    }

    settings[0].settings_id = NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS;
    settings[0].value = (uint32_t)session->max_stream_count;
    settings[1].settings_id = NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE;
    settings[1].value = h2_config_geti(config, H2_CONF_WIN_SIZE);
    settings[2].settings_id = NGHTTP2_SETTINGS_MAX_HEADER_LIST_SIZE;
    settings[2].value = 64*1024;
    
    *rv = nghttp2_submit_settings(session->ngh2, NGHTTP2_FLAG_NONE,
                                 settings,
                                 sizeof(settings)/sizeof(settings[0]));
    if (*rv != 0) {
        status = APR_EGENERAL;
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02935) "nghttp2_submit_settings: %s", 
                      nghttp2_strerror(*rv));
    }
    
    return status;
}

static int h2_session_want_write(h2_session *session)
{
    return nghttp2_session_want_write(session->ngh2);
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
        if (h2_mplx_out_has_data_for(stream->m, stream->id)) {
            int rv;
            h2_stream_set_suspended(stream, 0);
            ++rctx->resume_count;
            
            rv = nghttp2_session_resume_data(session->ngh2, stream->id);
            ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
