    NGH2_SET_CALLBACK(*pcb, send_data, on_send_data_cb);
    NGH2_SET_CALLBACK(*pcb, on_frame_send, on_frame_send_cb);

    return APR_SUCCESS;
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
    if (session->c) {
        h2_ctx_clear(session->c);
    }
    if (session->ngh2) {
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
    }
    if (session->spare) {
        apr_pool_destroy(session->spare);
        session->spare = NULL;
    }
}

static void h2_session_destroy(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    h2_session_cleanup(session);

    if (APLOGctrace1(session->c)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_session(%ld): destroy, %d streams open",
                      session->id, (int)h2_ihash_count(session->streams));
    }
    if (session->mplx) {
        h2_mplx_set_consumed_cb(session->mplx, NULL, NULL);
        h2_mplx_release_and_join(session->mplx, session->iowait);
        session->mplx = NULL;
    }
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}

static apr_status_t h2_session_shutdown(h2_session *session, int error, 
                                        const char *msg, int force_close)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(session);
    if (!msg && error) {
        msg = nghttp2_strerror(error);
    }
    
    if (error || force_close) {
        /* not a graceful shutdown, we want to leave... 
         * Do not start further streams that are waiting to be scheduled. 
         * Find out the max stream id that we habe been processed or
         * are still actively working on.
         * Remove all streams greater than this number without submitting
         * a RST_STREAM frame, since that should be clear from the GOAWAY
         * we send. */
        session->local.accepted_max = h2_mplx_shutdown(session->mplx);
        session->local.error = error;
    }
    else {
        /* graceful shutdown. we will continue processing all streams
         * we have, but no longer accept new ones. Report the max stream
         * we have received and discard all new ones. */
    }
    nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
                          session->local.accepted_max, 
                          error, (uint8_t*)msg, msg? strlen(msg):0);
    status = nghttp2_session_send(session->ngh2);
    if (status == APR_SUCCESS) {
        status = h2_conn_io_flush(&session->io);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03069)
                  "session(%ld): sent GOAWAY, err=%d, msg=%s", 
                  session->id, error, msg? msg : "");
    dispatch_event(session, H2_SESSION_EV_LOCAL_GOAWAY, error, msg);
    
    if (force_close) {
        h2_mplx_abort(session->mplx);
    }
    
    return status;
}

static apr_status_t session_pool_cleanup(void *data)
{
    h2_session *session = data;
    /* On a controlled connection shutdown, this gets never
     * called as we deregister and destroy our pool manually.
     * However when we have an async mpm, and handed it our idle
     * connection, it will just cleanup once the connection is closed
     * from the other side (and sometimes even from out side) and
     * here we arrive then.
     */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "session(%ld): pool_cleanup", session->id);
    
    if (session->state != H2_SESSION_ST_DONE 
        && session->state != H2_SESSION_ST_LOCAL_SHUTDOWN) {
        /* Not good. The connection is being torn down and we have
         * not sent a goaway. This is considered a protocol error and
         * the client has to assume that any streams "in flight" may have
         * been processed and are not safe to retry.
         * As clients with idle connection may only learn about a closed
         * connection when sending the next request, this has the effect
         * that at least this one request will fail.
         */
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, session->c, APLOGNO(03199)
                      "session(%ld): connection disappeared without proper "
                      "goodbye, clients will be confused, should not happen", 
                      session->id);
    }
    /* keep us from destroying the pool, since that is already ongoing. */
    session->pool = NULL;
    h2_session_destroy(session);
    return APR_SUCCESS;
}

