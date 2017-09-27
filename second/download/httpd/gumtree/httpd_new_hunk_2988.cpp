    if (r[0] == '!' && r[1] == '\0')
        return NULL;

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    /* Distinguish the balancer from worker */
    if (ap_proxy_valid_balancer_name(r, 9)) {
        proxy_balancer *balancer = ap_proxy_get_balancer(cmd->pool, conf, r, 0);
        if (!balancer) {
            const char *err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, r, f, 0);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        else {
            ap_proxy_update_balancer(cmd->pool, balancer, f);
        }
        for (i = 0; i < arr->nelts; i++) {
            const char *err = set_balancer_param(conf, cmd->pool, balancer, elts[i].key,
                                                 elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        new->balancer = balancer;
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, NULL, conf, r);
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
                         worker->s->name, new->real);
        }

        for (i = 0; i < arr->nelts; i++) {
            if (reuse) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01146)
                             "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                             elts[i].key, elts[i].val, worker->s->name);
            } else {
                const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                   elts[i].val);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            }
