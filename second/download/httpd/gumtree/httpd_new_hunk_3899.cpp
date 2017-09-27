        }
        
    }
    return session;
}

h2_session *h2_session_create(conn_rec *c, const h2_config *config, 
                              h2_workers *workers)
{
    return h2_session_create_int(c, NULL, config, workers);
}

h2_session *h2_session_rcreate(request_rec *r, const h2_config *config, 
                               h2_workers *workers)
{
    return h2_session_create_int(r->connection, r, config, workers);
}

static void h2_session_cleanup(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    /* This is an early cleanup of the session that may
     * discard what is no longer necessary for *new* streams
     * and general HTTP/2 processing.
     * At this point, all frames are in transit or somehwere in
     * our buffers or passed down output filters.
     * h2 streams might still being written out.
     */
    if (session->ngh2) {
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
    }
    if (session->spare) {
        apr_pool_destroy(session->spare);
        session->spare = NULL;
    }
}

void h2_session_destroy(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    h2_session_cleanup(session);
    
    if (session->mplx) {
        h2_mplx_release_and_join(session->mplx, session->iowait);
        session->mplx = NULL;
    }
    if (session->streams) {
        if (!h2_stream_set_is_empty(session->streams)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session(%ld): destroy, %d streams open",
                          session->id, (int)h2_stream_set_size(session->streams));
        }
        h2_stream_set_destroy(session->streams);
        session->streams = NULL;
    }
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}


void h2_session_eoc_callback(h2_session *session)
{
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
