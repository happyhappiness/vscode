        memcpy(shm, worker->s, sizeof(proxy_worker_shared));
        if (worker->s->was_malloced)
            free(worker->s); /* was malloced in ap_proxy_define_worker */
    } else {
        action = "re-using";
    }
    worker->s = shm;
    worker->s->index = i;
    {
        apr_pool_t *pool;
        apr_pool_create(&pool, ap_server_conf->process->pool);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02338)
                     "%s shm[%d] (0x%pp) for worker: %s", action, i, (void *)shm,
                     ap_proxy_worker_name(pool, worker));
        if (pool) {
            apr_pool_destroy(pool);
        }
    }
    return APR_SUCCESS;
}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    int mpm_threads;

    if (worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00924)
                     "worker %s shared already initialized",
                     ap_proxy_worker_name(p, worker));
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00925)
                     "initializing worker %s shared",
                     ap_proxy_worker_name(p, worker));
        /* Set default parameters */
        if (!worker->s->retry_set) {
            worker->s->retry = apr_time_from_sec(PROXY_WORKER_DEFAULT_RETRY);
        }
        /* By default address is reusable unless DisableReuse is set */
        if (worker->s->disablereuse) {
