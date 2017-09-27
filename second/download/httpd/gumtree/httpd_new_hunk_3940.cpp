AP_DECLARE(const char *) ap_get_protocol(conn_rec *c)
{
    const char *protocol = ap_run_protocol_get(c);
    return protocol? protocol : AP_PROTOCOL_HTTP1;
}

AP_DECLARE(apr_status_t) ap_get_protocol_upgrades(conn_rec *c, request_rec *r, 
                                                  server_rec *s, int report_all, 
                                                  const apr_array_header_t **pupgrades)
{
    apr_pool_t *pool = r? r->pool : c->pool;
    core_server_config *conf;
    const char *existing;
    apr_array_header_t *upgrades = NULL;

    if (!s) {
        s = (r? r->server : c->base_server);
    }
    conf = ap_get_core_module_config(s->module_config);
    
    if (conf->protocols->nelts > 0) {
        existing = ap_get_protocol(c);
        if (conf->protocols->nelts > 1 
            || !ap_array_str_contains(conf->protocols, existing)) {
            int i;
            
            /* possibly more than one choice or one, but not the
             * existing. (TODO: maybe 426 and Upgrade then?) */
            upgrades = apr_array_make(pool, conf->protocols->nelts + 1, 
                                      sizeof(char *));
            for (i = 0; i < conf->protocols->nelts; i++) {
                const char *p = APR_ARRAY_IDX(conf->protocols, i, char *);
                if (strcmp(existing, p)) {
                    /* not the one we have and possible, add in this order */
                    APR_ARRAY_PUSH(upgrades, const char*) = p;
                }
                else if (!report_all) {
                    break;
                }
            }
        }
    }
    
    *pupgrades = upgrades;
    return APR_SUCCESS;
}

AP_DECLARE(const char *) ap_select_protocol(conn_rec *c, request_rec *r, 
                                            server_rec *s,
                                            const apr_array_header_t *choices)
{
    apr_pool_t *pool = r? r->pool : c->pool;
    core_server_config *conf;
    const char *protocol = NULL, *existing;
    apr_array_header_t *proposals;

    if (!s) {
        s = (r? r->server : c->base_server);
    }
    conf = ap_get_core_module_config(s->module_config);
    
    if (APLOGcdebug(c)) {
        const char *p = apr_array_pstrcat(pool, conf->protocols, ',');
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
                      "select protocol from %s, choices=%s for server %s", 
                      p, apr_array_pstrcat(pool, choices, ','),
                      s->server_hostname);
