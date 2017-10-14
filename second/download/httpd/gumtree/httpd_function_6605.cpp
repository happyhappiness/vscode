static apr_status_t proxy_session_pre_close(void *theconn)
{
    proxy_conn_rec *p_conn = (proxy_conn_rec *)theconn;
    h2_proxy_session *session = p_conn->data;

    if (session && session->ngh2) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                      "proxy_session(%s): pool cleanup, state=%d, streams=%d",
                      session->id, session->state, 
                      (int)h2_ihash_count(session->streams));
        session->aborted = 1;
        dispatch_event(session, H2_PROXYS_EV_PRE_CLOSE, 0, NULL);
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
        p_conn->data = NULL;
    }
    return APR_SUCCESS;
}