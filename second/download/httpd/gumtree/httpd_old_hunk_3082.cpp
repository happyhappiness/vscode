    if (conn->worker->cp->pool) {
        apr_pool_destroy(conn->pool);
    }

    return APR_SUCCESS;
}
#endif

/*
 * ap_proxy_initialize_worker_share() concerns itself
 * with initializing those parts of worker which
 * are, or could be, shared. Basically worker->s
 */
PROXY_DECLARE(void) ap_proxy_initialize_worker_share(proxy_server_conf *conf,
                                                     proxy_worker *worker,
                                                     server_rec *s)
{
    proxy_worker_stat *score = NULL;

    if (PROXY_WORKER_IS_INITIALIZED(worker)) {
        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                     "proxy: worker %s already initialized",
                     worker->name);
        return;
    }
    if (!worker->s) {
        /* Get scoreboard slot */
        if (ap_scoreboard_image) {
            score = (proxy_worker_stat *) ap_get_scoreboard_lb(worker->id);
            if (!score) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "proxy: ap_get_scoreboard_lb(%d) failed in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);
            }
            else {
                 ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                      "proxy: grabbed scoreboard slot %d in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);
            }
        }
        if (!score) {
            score = (proxy_worker_stat *) apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                  "proxy: initialized plain memory in child %" APR_PID_T_FMT " for worker %s",
                  getpid(), worker->name);
        }
        worker->s = score;
        /*
         * recheck to see if we've already been here. Possible
         * if proxy is using scoreboard to hold shared stats
         */
        if (PROXY_WORKER_IS_INITIALIZED(worker)) {
            /* The worker share is already initialized */
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                         "proxy: worker %s already initialized",
                         worker->name);
            return;
        }
    }
    if (worker->route) {
        strcpy(worker->s->route, worker->route);
    }
    else {
        *worker->s->route = '\0';
    }
    if (worker->redirect) {
        strcpy(worker->s->redirect, worker->redirect);
    }
    else {
        *worker->s->redirect = '\0';
    }

    worker->s->status |= (worker->status | PROXY_WORKER_INITIALIZED);
    worker->s->apr_hash = worker->apr_hash;
    worker->s->our_hash = worker->our_hash;

}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s, apr_pool_t *p)
{
    apr_status_t rv;

#if APR_HAS_THREADS
    int mpm_threads;
#endif

    if (worker->status & PROXY_WORKER_INITIALIZED) {
        /* The worker is already initialized */
        return APR_SUCCESS;
    }

    /* Set default parameters */
    if (!worker->retry_set) {
        worker->retry = apr_time_from_sec(PROXY_WORKER_DEFAULT_RETRY);
    }
    /* By default address is reusable unless DisableReuse is set */
    if (worker->disablereuse) {
        worker->is_address_reusable = 0;
    }
    else {
        worker->is_address_reusable = 1;
    }

    if (worker->cp == NULL)
        init_conn_pool(p, worker);
    if (worker->cp == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
            "can not create connection pool");
        return APR_EGENERAL;
    } 

#if APR_HAS_THREADS
    if (worker->mutex == NULL) {
        rv = apr_thread_mutex_create(&(worker->mutex), APR_THREAD_MUTEX_DEFAULT, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                "can not create thread mutex");
            return rv;
        }
    }

    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
    if (mpm_threads > 1) {
        /* Set hard max to no more then mpm_threads */
        if (worker->hmax == 0 || worker->hmax > mpm_threads) {
            worker->hmax = mpm_threads;
        }
        if (worker->smax == -1 || worker->smax > worker->hmax) {
            worker->smax = worker->hmax;
        }
        /* Set min to be lower then smax */
        if (worker->min > worker->smax) {
            worker->min = worker->smax;
        }
    }
    else {
        /* This will supress the apr_reslist creation */
        worker->min = worker->smax = worker->hmax = 0;
    }
    if (worker->hmax) {
        rv = apr_reslist_create(&(worker->cp->res),
                                worker->min, worker->smax,
                                worker->hmax, worker->ttl,
                                connection_constructor, connection_destructor,
                                worker, worker->cp->pool);

        apr_pool_cleanup_register(worker->cp->pool, (void *)worker,
                                  conn_pool_cleanup,
                                  apr_pool_cleanup_null);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
            "proxy: initialized worker %d in child %" APR_PID_T_FMT " for (%s) min=%d max=%d smax=%d",
             worker->id, getpid(), worker->hostname, worker->min,
             worker->hmax, worker->smax);

#if (APR_MAJOR_VERSION > 0)
        /* Set the acquire timeout */
        if (rv == APR_SUCCESS && worker->acquire_set) {
            apr_reslist_timeout_set(worker->cp->res, worker->acquire);
        }
#endif
    }
    else
#endif
    {
        void *conn;

        rv = connection_constructor(&conn, worker, worker->cp->pool);
        worker->cp->conn = conn;

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
             "proxy: initialized single connection worker %d in child %" APR_PID_T_FMT " for (%s)",
             worker->id, getpid(), worker->hostname);
    }
    if (rv == APR_SUCCESS) {
        worker->status |= (PROXY_WORKER_INITIALIZED);
    }
    return rv;
}

PROXY_DECLARE(int) ap_proxy_retry_worker(const char *proxy_function,
                                         proxy_worker *worker,
                                         server_rec *s)
{
    if (worker->s->status & PROXY_WORKER_IN_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                    "proxy: %s: retrying the worker for (%s)",
                     proxy_function, worker->hostname);
        if (apr_time_now() > worker->s->error_time + worker->retry) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: %s: worker for (%s) has been marked for retry",
                         proxy_function, worker->hostname);
            return OK;
        }
        else {
            return DECLINED;
        }
    }
    else {
        return OK;
    }
}

PROXY_DECLARE(int) ap_proxy_acquire_connection(const char *proxy_function,
                                               proxy_conn_rec **conn,
                                               proxy_worker *worker,
                                               server_rec *s)
{
    apr_status_t rv;

    if (!PROXY_WORKER_IS_USABLE(worker)) {
        /* Retry the worker */
        ap_proxy_retry_worker(proxy_function, worker, s);

        if (!PROXY_WORKER_IS_USABLE(worker)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "proxy: %s: disabled connection for (%s)",
                         proxy_function, worker->hostname);
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }
#if APR_HAS_THREADS
    if (worker->hmax && worker->cp->res) {
        rv = apr_reslist_acquire(worker->cp->res, (void **)conn);
    }
    else
#endif
    {
        /* create the new connection if the previous was destroyed */
        if (!worker->cp->conn) {
            connection_constructor((void **)conn, worker, worker->cp->pool);
        }
        else {
            *conn = worker->cp->conn;
            worker->cp->conn = NULL;
        }
        rv = APR_SUCCESS;
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "proxy: %s: failed to acquire connection for (%s)",
                     proxy_function, worker->hostname);
        return HTTP_SERVICE_UNAVAILABLE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has acquired connection for (%s)",
                 proxy_function, worker->hostname);

    (*conn)->worker = worker;
    (*conn)->close  = 0;
#if APR_HAS_THREADS
    (*conn)->inreslist = 0;
#endif

    return OK;
}

PROXY_DECLARE(int) ap_proxy_release_connection(const char *proxy_function,
                                               proxy_conn_rec *conn,
                                               server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has released connection for (%s)",
                 proxy_function, conn->worker->hostname);
    connection_cleanup(conn);

    return OK;
}

PROXY_DECLARE(int)
