    proxy_worker **worker;
    proxy_worker *mycandidate = NULL;
    int checking_standby;
    int checked_standby;
    rr_data *ctx;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01116)
                 "proxy: Entering roundrobin for BALANCER %s (%d)",
                 balancer->name, (int)getpid());

    /* The index of the candidate last chosen is stored in ctx->index */
    if (!balancer->context) {
        /* UGLY */
        ctx = apr_pcalloc(r->server->process->pconf, sizeof(rr_data));
        balancer->context = (void *)ctx;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01117)
                 "proxy: Creating roundrobin ctx for BALANCER %s (%d)",
                 balancer->name, (int)getpid());
    } else {
        ctx = (rr_data *)balancer->context;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01118)
                 "proxy: roundrobin index: %d (%d)",
                 ctx->index, (int)getpid());

    checking_standby = checked_standby = 0;
    while (!mycandidate && !checked_standby) {
        worker = (proxy_worker **)balancer->workers->elts;

        for (i = 0; i < balancer->workers->nelts; i++, worker++) {
            if (i < ctx->index)
                continue;
            if (
                (checking_standby ? !PROXY_WORKER_IS_STANDBY(*worker) : PROXY_WORKER_IS_STANDBY(*worker)) ||
                (PROXY_WORKER_IS_DRAINING(*worker))
                ) {
                continue;
            }
            if (!PROXY_WORKER_IS_USABLE(*worker))
                ap_proxy_retry_worker("BALANCER", *worker, r->server);
            if (PROXY_WORKER_IS_USABLE(*worker)) {
                mycandidate = *worker;
                break;
            }
