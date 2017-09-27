            const char *svc_ma = "";
            int secure = h2_h2_is_tls(r->connection);
            int ma = h2_config_geti(cfg, H2_CONF_ALT_SVC_MAX_AGE);
            if (ma >= 0) {
                svc_ma = apr_psprintf(r->pool, "; ma=%d", ma);
            }
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03043)
                          "h2_alt_svc: announce %s for %s:%d", 
                          (secure? "secure" : "insecure"), 
                          r->hostname, (int)r->server->port);
            for (i = 0; i < cfg->alt_svcs->nelts; ++i) {
                h2_alt_svc *as = h2_alt_svc_IDX(cfg->alt_svcs, i);
                const char *ahost = as->host;
