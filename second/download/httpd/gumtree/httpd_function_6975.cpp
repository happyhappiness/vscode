static void * APR_THREAD_FUNC hc_check(apr_thread_t *thread, void *b)
{
    baton_t *baton = (baton_t *)b;
    sctx_t *ctx = baton->ctx;
    apr_time_t now = baton->now;
    proxy_worker *worker = baton->worker;
    apr_pool_t *ptemp = baton->ptemp;
    server_rec *s = ctx->s;
    apr_status_t rv;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03256)
                 "%sHealth checking %s", (thread ? "Threaded " : ""), worker->s->name);

    switch (worker->s->method) {
        case TCP:
            rv = hc_check_tcp(ctx, ptemp, worker);
            break;

        case OPTIONS:
        case HEAD:
        case GET:
             rv = hc_check_http(ctx, ptemp, worker);
             break;

        default:
            rv = APR_ENOTIMPL;
            break;
    }
    if (rv == APR_ENOTIMPL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(03257)
                         "Somehow tried to use unimplemented hcheck method: %d",
                         (int)worker->s->method);
        apr_pool_destroy(ptemp);
        return NULL;
    }
    /* what state are we in ? */
    if (PROXY_WORKER_IS_HCFAILED(worker)) {
        if (rv == APR_SUCCESS) {
            worker->s->pcount += 1;
            if (worker->s->pcount >= worker->s->passes) {
                ap_proxy_set_wstatus(PROXY_WORKER_HC_FAIL_FLAG, 0, worker);
                ap_proxy_set_wstatus(PROXY_WORKER_IN_ERROR_FLAG, 0, worker);
                worker->s->pcount = 0;
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03302)
                             "%sHealth check ENABLING %s", (thread ? "Threaded " : ""),
                             worker->s->name);

            }
        }
    } else {
        if (rv != APR_SUCCESS) {
            worker->s->error_time = now;
            worker->s->fcount += 1;
            if (worker->s->fcount >= worker->s->fails) {
                ap_proxy_set_wstatus(PROXY_WORKER_HC_FAIL_FLAG, 1, worker);
                worker->s->fcount = 0;
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03303)
                             "%sHealth check DISABLING %s", (thread ? "Threaded " : ""),
                             worker->s->name);
            }
        }
    }
    worker->s->updated = now;
    apr_pool_destroy(ptemp);
    return NULL;
}