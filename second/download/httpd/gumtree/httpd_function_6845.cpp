static apr_status_t session_cleanup(h2_session *session, const char *trigger)
{
    conn_rec *c = session->c;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  H2_SSSN_MSG(session, "pool_cleanup"));
    
    if (session->state != H2_SESSION_ST_DONE
        && session->state != H2_SESSION_ST_INIT) {
        /* Not good. The connection is being torn down and we have
         * not sent a goaway. This is considered a protocol error and
         * the client has to assume that any streams "in flight" may have
         * been processed and are not safe to retry.
         * As clients with idle connection may only learn about a closed
         * connection when sending the next request, this has the effect
         * that at least this one request will fail.
         */
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                      H2_SSSN_LOG(APLOGNO(03199), session, 
                      "connection disappeared without proper "
                      "goodbye, clients will be confused, should not happen"));
    }

    transit(session, trigger, H2_SESSION_ST_CLEANUP);
    h2_mplx_release_and_join(session->mplx, session->iowait);
    session->mplx = NULL;

    ap_assert(session->ngh2);
    nghttp2_session_del(session->ngh2);
    session->ngh2 = NULL;
    h2_ctx_clear(c);
    
    
    return APR_SUCCESS;
}