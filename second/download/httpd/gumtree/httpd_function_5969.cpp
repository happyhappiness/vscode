static int h2_alt_svc_handler(request_rec *r)
{
    h2_ctx *ctx;
    const h2_config *cfg;
    int i;
    
    if (r->connection->keepalives > 0) {
        /* Only announce Alt-Svc on the first response */
        return DECLINED;
    }
    
    ctx = h2_ctx_rget(r);
    if (h2_ctx_is_active(ctx) || h2_ctx_is_task(ctx)) {
        return DECLINED;
    }
    
    cfg = h2_config_rget(r);
    if (r->hostname && cfg && cfg->alt_svcs && cfg->alt_svcs->nelts > 0) {
        const char *alt_svc_used = apr_table_get(r->headers_in, "Alt-Svc-Used");
        if (!alt_svc_used) {
            /* We have alt-svcs defined and client is not already using
             * one, announce the services that were configured and match. 
             * The security of this connection determines if we allow
             * other host names or ports only.
             */
            const char *alt_svc = "";
            const char *svc_ma = "";
            int secure = h2_h2_is_tls(r->connection);
            int ma = h2_config_geti(cfg, H2_CONF_ALT_SVC_MAX_AGE);
            if (ma >= 0) {
                svc_ma = apr_psprintf(r->pool, "; ma=%d", ma);
            }
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "h2_alt_svc: announce %s for %s:%d", 
                          (secure? "secure" : "insecure"), 
                          r->hostname, (int)r->server->port);
            for (i = 0; i < cfg->alt_svcs->nelts; ++i) {
                h2_alt_svc *as = h2_alt_svc_IDX(cfg->alt_svcs, i);
                const char *ahost = as->host;
                if (ahost && !apr_strnatcasecmp(ahost, r->hostname)) {
                    ahost = NULL;
                }
                if (secure || !ahost) {
                    alt_svc = apr_psprintf(r->pool, "%s%s%s=\"%s:%d\"%s", 
                                           alt_svc,
                                           (*alt_svc? ", " : ""), as->alpn,
                                           ahost? ahost : "", as->port,
                                           svc_ma);
                }
            }
            if (*alt_svc) {
                apr_table_set(r->headers_out, "Alt-Svc", alt_svc);
            }
        }
    }
    
    return DECLINED;
}