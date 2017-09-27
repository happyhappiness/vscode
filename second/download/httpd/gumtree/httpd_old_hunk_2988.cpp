    if (r[0] == '!' && r[1] == '\0')
        return NULL;

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    /* Distinguish the balancer from worker */
    if (strncasecmp(r, "balancer:", 9) == 0) {
        proxy_balancer *balancer = ap_proxy_get_balancer(cmd->pool, conf, r);
        if (!balancer) {
            const char *err = ap_proxy_add_balancer(&balancer,
                                                    cmd->pool,
                                                    conf, r);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        for (i = 0; i < arr->nelts; i++) {
            const char *err = set_balancer_param(conf, cmd->pool, balancer, elts[i].key,
                                                 elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, conf, r);
        int reuse = 0;
        if (!worker) {
            const char *err = ap_proxy_add_worker(&worker, cmd->pool, conf, r);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            PROXY_COPY_CONF_PARAMS(worker, conf);
        } else {
            reuse = 1;
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         worker->name, new->real);
        }

        for (i = 0; i < arr->nelts; i++) {
            if (reuse) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                             elts[i].key, elts[i].val, worker->name);
            } else {
                const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                   elts[i].val);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            }
