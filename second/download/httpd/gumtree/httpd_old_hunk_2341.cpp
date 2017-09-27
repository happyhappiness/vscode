    /* Try to find existing worker */
    worker = ap_proxy_get_worker(cmd->temp_pool, conf, name);
    if (!worker) {
        const char *err;
        if ((err = ap_proxy_add_worker(&worker, cmd->pool, conf, name)) != NULL)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
    } else {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                     "worker %s already used by another worker", worker->name);
    }
    PROXY_COPY_CONF_PARAMS(worker, conf);

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    for (i = 0; i < arr->nelts; i++) {
        const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                           elts[i].val);
        if (err)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
    }
    /* Try to find the balancer */
    balancer = ap_proxy_get_balancer(cmd->temp_pool, conf, path);
    if (!balancer) {
        const char *err = ap_proxy_add_balancer(&balancer,
                                                cmd->pool,
