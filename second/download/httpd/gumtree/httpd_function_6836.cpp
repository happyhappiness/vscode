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
    
    if (session->state != H2_SESSION_ST_DONE) {
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