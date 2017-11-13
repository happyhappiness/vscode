apr_status_t h2_conn_process(conn_rec *c, request_rec *r, server_rec *s)
{
    apr_status_t status;
    h2_session *session;
    const h2_config *config;
    int rv;
    
    if (!workers) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02911) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "h2_conn_process start");
    
    if (!s && r) {
        s = r->server;
    }
    
    config = s? h2_config_sget(s) : h2_config_get(c);
    if (r) {
        session = h2_session_rcreate(r, config, workers);
    }
    else {
        session = h2_session_create(c, config, workers);
    }
    
    if (!h2_is_acceptable_connection(c, 1)) {
        nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 0,
                              NGHTTP2_INADEQUATE_SECURITY, NULL, 0);
    } 

    ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);
    status = h2_session_start(session, &rv);
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): starting on %s:%d", session->id,
                  session->c->base_server->server_hostname,
                  session->c->local_addr->port);
    if (status != APR_SUCCESS) {
        h2_session_abort(session, status, rv);
        h2_session_eoc_callback(session);
        return status;
    }
    
    status = h2_session_process(session);

    ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): done", session->id);
    /* Make sure this connection gets closed properly. */
    ap_update_child_status_from_conn(c->sbh, SERVER_CLOSING, c);
    c->keepalive = AP_CONN_CLOSE;
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }

    h2_session_close(session);
    /* hereafter session will be gone */
    return status;
}