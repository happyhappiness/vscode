        err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, path, "/", 0);
        if (err)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
    }

    /* Try to find existing worker */
    worker = ap_proxy_get_worker(cmd->temp_pool, balancer, conf, name);
    if (!worker) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01147)
                     "Defining worker '%s' for balancer '%s'",
                     name, balancer->s->name);
        if ((err = ap_proxy_define_worker(cmd->pool, &worker, balancer, conf, name, 0)) != NULL)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01148)
                     "Defined worker '%s' for balancer '%s'",
                     worker->s->name, balancer->s->name);
        PROXY_COPY_CONF_PARAMS(worker, conf);
    } else {
        reuse = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01149)
                     "Sharing worker '%s' instead of creating new worker '%s'",
                     worker->s->name, name);
    }

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    for (i = 0; i < arr->nelts; i++) {
        if (reuse) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01150)
                         "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                         elts[i].key, elts[i].val, worker->s->name);
        } else {
            err = set_worker_param(cmd->pool, worker, elts[i].key,
                                               elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        }
