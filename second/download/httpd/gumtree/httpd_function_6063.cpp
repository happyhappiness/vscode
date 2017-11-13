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