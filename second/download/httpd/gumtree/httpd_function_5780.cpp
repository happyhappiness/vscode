apr_status_t h2_conn_main(conn_rec *c)
{
    h2_config *config = h2_config_get(c);
    h2_session *session;
    apr_status_t status;
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "h2_conn_main start");
    if (!workers) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02912) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    session = h2_session_create(c, config, workers);
    if (!session) {
        return APR_EGENERAL;
    }
    
    status = h2_session_process(session);

    /* Make sure this connection gets closed properly. */
    c->keepalive = AP_CONN_CLOSE;
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }

    return status;
}