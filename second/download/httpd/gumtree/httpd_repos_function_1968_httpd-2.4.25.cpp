static apr_status_t hc_watchdog_callback(int state, void *data,
                                         apr_pool_t *pool)
{
    apr_status_t rv = APR_SUCCESS;
    apr_time_t now = apr_time_now();
    proxy_balancer *balancer;
    sctx_t *ctx = (sctx_t *)data;
    server_rec *s = ctx->s;
    proxy_server_conf *conf;
    switch (state) {
        case AP_WATCHDOG_STATE_STARTING:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03258)
                         "%s watchdog started.",
                         HCHECK_WATHCHDOG_NAME);
#if HC_USE_THREADS
            if (ctx->tpsize) {
                rv =  apr_thread_pool_create(&ctx->hctp, ctx->tpsize,
                                             ctx->tpsize, ctx->p);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_INFO, rv, s, APLOGNO(03312)
                                 "apr_thread_pool_create() with %d threads failed",
                                 ctx->tpsize);
                    /* we can continue on without the threadpools */
                    ctx->hctp = NULL;
                } else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(03313)
                                 "apr_thread_pool_create() with %d threads succeeded",
                                 ctx->tpsize);
                }
            } else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(03314)
                             "Skipping apr_thread_pool_create()");
                ctx->hctp = NULL;
            }

#endif
            break;

        case AP_WATCHDOG_STATE_RUNNING:
            /* loop thru all workers */
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                         "Run of %s watchdog.",
                         HCHECK_WATHCHDOG_NAME);
            if (s) {
                int i;
                conf = (proxy_server_conf *) ap_get_module_config(s->module_config, &proxy_module);
                balancer = (proxy_balancer *)conf->balancers->elts;
                for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
                    int n;
                    proxy_worker **workers;
                    proxy_worker *worker;
                    /* Have any new balancers or workers been added dynamically? */
                    ap_proxy_sync_balancer(balancer, s, conf);
                    workers = (proxy_worker **)balancer->workers->elts;
                    for (n = 0; n < balancer->workers->nelts; n++) {
                        worker = *workers;
                        if (!PROXY_WORKER_IS(worker, PROXY_WORKER_STOPPED) &&
                           (worker->s->method != NONE) &&
                           (now > worker->s->updated + worker->s->interval)) {
                            baton_t *baton;
                            /* This pool must last the lifetime of the (possible) thread */
                            apr_pool_t *ptemp;
                            apr_pool_create(&ptemp, ctx->p);
                            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                                         "Checking %s worker: %s  [%d] (%pp)", balancer->s->name,
                                         worker->s->name, worker->s->method, worker);

                            if ((rv = hc_init_worker(ctx, worker)) != APR_SUCCESS) {
                                return rv;
                            }
                            baton = apr_palloc(ptemp, sizeof(baton_t));
                            baton->ctx = ctx;
                            baton->now = now;
                            baton->worker = worker;
                            baton->ptemp = ptemp;

                            if (!ctx->hctp) {
                                hc_check(NULL, baton);
                            }
#if HC_USE_THREADS
                            else {
                                rv = apr_thread_pool_push(ctx->hctp, hc_check, (void *)baton,
                                                          APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
                            }
#endif
                        }
                        workers++;
                    }
                }
                /* s = s->next; */
            }
            break;

        case AP_WATCHDOG_STATE_STOPPING:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03261)
                         "stopping %s watchdog.",
                         HCHECK_WATHCHDOG_NAME);
#if HC_USE_THREADS
            rv =  apr_thread_pool_destroy(ctx->hctp);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_INFO, rv, s, APLOGNO(03315)
                             "apr_thread_pool_destroy() failed");
            }
#endif
            ctx->hctp = NULL;
            break;
    }
    return rv;
}