        apr_pool_destroy(conn->pool);

    return APR_SUCCESS;
}
#endif

PROXY_DECLARE(void) ap_proxy_initialize_worker_share(proxy_server_conf *conf,
                                                     proxy_worker *worker,
                                                     server_rec *s)
{
#if PROXY_HAS_SCOREBOARD
    lb_score *score = NULL;
#else
    void *score = NULL;
#endif

    if (worker->s && worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker share is already initialized */
        return;
    }
#if PROXY_HAS_SCOREBOARD
        /* Get scoreboard slot */
    if (ap_scoreboard_image) {
        score = ap_get_scoreboard_lb(worker->id);
    if (!score)
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
              "proxy: ap_get_scoreboard_lb(%d) failed for worker %s",
              worker->id, worker->name);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized scoreboard slot %d for worker %s",
              worker->id, worker->name);
    }
#endif
    if (!score) {
        score = apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized plain memory for worker %s",
              worker->name);
    }
    worker->s = (proxy_worker_stat *)score;
    if (worker->route)
        strcpy(worker->s->route, worker->route);
    else
        *worker->s->route = '\0';
    if (worker->redirect)
        strcpy(worker->s->redirect, worker->redirect);
    else
        *worker->s->redirect = '\0';
    /* Set default parameters */
    if (!worker->retry)
        worker->retry = apr_time_from_sec(PROXY_WORKER_DEFAULT_RETRY);
    /* By default address is reusable */
    worker->is_address_reusable = 1;

}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s)
{
    apr_status_t rv;

#if APR_HAS_THREADS
    int mpm_threads;
#endif

    if (worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker is already initialized */
        return APR_SUCCESS;
    }

#if APR_HAS_THREADS
    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
    if (mpm_threads > 1) {
        /* Set hard max to no more then mpm_threads */
        if (worker->hmax == 0 || worker->hmax > mpm_threads)
            worker->hmax = mpm_threads;
