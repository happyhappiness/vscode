     * from the other side (and sometimes even from out side) and
     * here we arrive then.
     */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "session(%ld): pool_cleanup", session->id);
    
    if (session->state != H2_SESSION_ST_DONE) {
        /* Not good. The connection is being torn down and we have
         * not sent a goaway. This is considered a protocol error and
         * the client has to assume that any streams "in flight" may have
         * been processed and are not safe to retry.
         * As clients with idle connection may only learn about a closed
         * connection when sending the next request, this has the effect
