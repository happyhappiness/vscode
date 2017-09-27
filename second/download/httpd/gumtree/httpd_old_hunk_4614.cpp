                             "%sHealth check DISABLING %s", (thread ? "Threaded " : ""),
                             worker->s->name);
            }
        }
    }
    worker->s->updated = now;
    apr_pool_destroy(ptemp);
    return NULL;
}

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
