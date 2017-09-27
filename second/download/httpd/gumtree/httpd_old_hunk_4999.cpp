        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00926)
                     "worker %s local already initialized", worker->s->name);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00927)
                     "initializing worker %s local", worker->s->name);
        /* Now init local worker data */
        if (worker->tmutex == NULL) {
            rv = apr_thread_mutex_create(&(worker->tmutex), APR_THREAD_MUTEX_DEFAULT, p);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00928)
                             "can not create worker thread mutex");
                return rv;
            }
        }
        if (worker->cp == NULL)
            init_conn_pool(p, worker);
        if (worker->cp == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00929)
                         "can not create connection pool");
            return APR_EGENERAL;
        }

        if (worker->s->hmax) {
            rv = apr_reslist_create(&(worker->cp->res),
                                    worker->s->min, worker->s->smax,
