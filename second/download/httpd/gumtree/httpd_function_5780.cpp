apr_status_t h2_conn_rprocess(request_rec *r)
{
    h2_config *config = h2_config_rget(r);
    h2_session *session;
    
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "h2_conn_process start");
    if (!workers) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02911) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    session = h2_session_rcreate(r, config, workers);
    if (!session) {
        return APR_EGENERAL;
    }
    
    return h2_session_process(session);
}