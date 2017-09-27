AP_DECLARE(const char *) ap_get_protocol(conn_rec *c)
{
    const char *protocol = ap_run_protocol_get(c);
    return protocol? protocol : AP_PROTOCOL_HTTP1;
}

AP_DECLARE(const char *) ap_select_protocol(conn_rec *c, request_rec *r, 
                                            server_rec *s,
                                            const apr_array_header_t *choices)
{
    apr_pool_t *pool = r? r->pool : c->pool;
    core_server_config *conf = ap_get_core_module_config(s->module_config);
    const char *protocol = NULL, *existing;
    apr_array_header_t *proposals;

    if (APLOGcdebug(c)) {
        const char *p = apr_array_pstrcat(pool, conf->protocols, ',');
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
                      "select protocol from %s, choices=%s for server %s", 
                      p, apr_array_pstrcat(pool, choices, ','),
                      s->server_hostname);
