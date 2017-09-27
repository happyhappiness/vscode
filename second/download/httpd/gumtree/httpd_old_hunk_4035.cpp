    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "session(%ld): cleanup and destroy", session->id);
    apr_pool_cleanup_kill(session->pool, session, session_pool_cleanup);
    h2_session_destroy(session);
}

static apr_status_t h2_session_abort_int(h2_session *session, int reason)
{
    AP_DEBUG_ASSERT(session);
    if (!session->aborted) {
        session->aborted = 1;
        
        if (session->ngh2) {            
            if (NGHTTP2_ERR_EOF == reason) {
                /* This is our way of indication that the connection is
                 * gone. No use to send any GOAWAY frames. */
                nghttp2_session_terminate_session(session->ngh2, reason);
            }
            else if (!reason) {
                nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
                                      session->max_stream_received, 
                                      reason, NULL, 0);
                nghttp2_session_send(session->ngh2);
            }
            else {
                const char *err = nghttp2_strerror(reason);
                
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                              "session(%ld): aborting session, reason=%d %s",
                              session->id, reason, err);
                
                /* The connection might still be there and we shut down
                 * with GOAWAY and reason information. */
                nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
                                      session->max_stream_received, 
                                      reason, (const uint8_t *)err, 
                                      strlen(err));
                nghttp2_session_send(session->ngh2);
            }
        }
        h2_mplx_abort(session->mplx);
    }
    return APR_SUCCESS;
}

apr_status_t h2_session_abort(h2_session *session, apr_status_t reason, int rv)
{
    AP_DEBUG_ASSERT(session);
    if (rv == 0) {
        rv = NGHTTP2_ERR_PROTO;
        switch (reason) {
            case APR_ENOMEM:
                rv = NGHTTP2_ERR_NOMEM;
                break;
            case APR_SUCCESS:                            /* all fine, just... */
            case APR_EOF:                         /* client closed its end... */
            case APR_TIMEUP:                          /* got bored waiting... */
                rv = 0;                            /* ...gracefully shut down */
                break;
            case APR_EBADF:        /* connection unusable, terminate silently */
            default:
                if (APR_STATUS_IS_ECONNABORTED(reason)
                    || APR_STATUS_IS_ECONNRESET(reason)
                    || APR_STATUS_IS_EBADF(reason)) {
                    rv = NGHTTP2_ERR_EOF;
                }
                break;
        }
    }
    return h2_session_abort_int(session, rv);
}

apr_status_t h2_session_start(h2_session *session, int *rv)
{
    apr_status_t status = APR_SUCCESS;
    nghttp2_settings_entry settings[3];
    size_t slen;
    int win_size;
    
