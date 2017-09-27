        q = &linger_q;
        cs->pub.state = CONN_STATE_LINGER_NORMAL;
    }
    apr_atomic_inc32(&lingering_count);
    apr_thread_mutex_lock(timeout_mutex);
    TO_QUEUE_APPEND(*q, cs);
    cs->pfd.reqevents = APR_POLLIN | APR_POLLHUP | APR_POLLERR;
    rv = apr_pollset_add(event_pollset, &cs->pfd);
    apr_thread_mutex_unlock(timeout_mutex);
    if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "start_lingering_close: apr_pollset_add failure");
        apr_thread_mutex_lock(timeout_mutex);
