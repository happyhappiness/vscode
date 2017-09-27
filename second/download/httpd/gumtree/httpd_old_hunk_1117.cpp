        ent = (struct proxy_alias *)conf->raliases->elts;
    }
    for (i = 0; i < conf->raliases->nelts; i++) {
        proxy_server_conf *sconf = (proxy_server_conf *)
            ap_get_module_config(r->server->module_config, &proxy_module);
        proxy_balancer *balancer;
        const char *real;
        real = ent[i].real;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "ppr: real: %s", real);
        /*
         * First check if mapping against a balancer and see
         * if we have such a entity. If so, then we need to
         * find the particulars of the actual worker which may
         * or may not be the right one... basically, we need
         * to find which member actually handled this request.
         */
        if ((strncasecmp(real, "balancer:", 9) == 0) &&
            (balancer = ap_proxy_get_balancer(r->pool, sconf, real))) {
            int n;
            proxy_worker *worker;
            worker = (proxy_worker *)balancer->workers->elts;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "ppr: checking balancer: %s",
                         balancer->name);
            for (n = 0; n < balancer->workers->nelts; n++) {
                if (worker->port) {
                    u = apr_psprintf(r->pool, "%s://%s:%d/", worker->scheme,
                                     worker->hostname, worker->port);
                }
                else {
                    u = apr_psprintf(r->pool, "%s://%s/", worker->scheme,
                                     worker->hostname);
                }
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "ppr: matching member (%s) and URL (%s)",
                         u, url);

                l2 = strlen(u);
                if (l1 >= l2 && strncasecmp(u, url, l2) == 0) {
                    u = apr_pstrcat(r->pool, ent[i].fake, &url[l2], NULL);
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "ppr: matched member (%s)", u);
                    return ap_construct_url(r->pool, u, r);
                }
                worker++;
            }
        }

        l2 = strlen(real);
        if (l1 >= l2 && strncasecmp(real, url, l2) == 0) {
            u = apr_pstrcat(r->pool, ent[i].fake, &url[l2], NULL);
            return ap_construct_url(r->pool, u, r);
        }
    }

    return url;
}

