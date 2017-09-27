        return "BalancerMember must define balancer name when outside <Proxy > section";
    if (!name)
        return "BalancerMember must define remote proxy server";

    ap_str_tolower(path);   /* lowercase scheme://hostname */

    /* Try to find existing worker */
    worker = ap_proxy_get_worker(cmd->temp_pool, conf, name);
    if (!worker) {
        const char *err;
        if ((err = ap_proxy_add_worker(&worker, cmd->pool, conf, name)) != NULL)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        PROXY_COPY_CONF_PARAMS(worker, conf);
    } else {
        reuse = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                     "Sharing worker '%s' instead of creating new worker '%s'",
                     worker->name, name);
    }

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    for (i = 0; i < arr->nelts; i++) {
        if (reuse) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                         elts[i].key, elts[i].val, worker->name);
        } else {
            const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                               elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        }
    }
    /* Try to find the balancer */
    balancer = ap_proxy_get_balancer(cmd->temp_pool, conf, path);
    if (!balancer) {
        const char *err = ap_proxy_add_balancer(&balancer,
                                                cmd->pool,
                                                conf, path);
        if (err)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
    }
    /* Add the worker to the load balancer */
    ap_proxy_add_worker_to_balancer(cmd->pool, balancer, worker);
    return NULL;
}

static const char *
    set_proxy_param(cmd_parms *cmd, void *dummy, const char *arg)
{
