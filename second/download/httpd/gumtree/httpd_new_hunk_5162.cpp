            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        new->balancer = balancer;
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, NULL, conf, de_socketfy(cmd->pool, r));
        int reuse = 0;
        if (!worker) {
            const char *err = ap_proxy_define_worker(cmd->pool, &worker, NULL, conf, r, 0);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);

            PROXY_COPY_CONF_PARAMS(worker, conf);
        } else {
            reuse = 1;
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01145)
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         ap_proxy_worker_name(cmd->pool, worker), new->real);
        }

        for (i = 0; i < arr->nelts; i++) {
            if (reuse) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01146)
                             "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                             elts[i].key, elts[i].val, ap_proxy_worker_name(cmd->pool, worker));
            } else {
                const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                   elts[i].val);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            }
