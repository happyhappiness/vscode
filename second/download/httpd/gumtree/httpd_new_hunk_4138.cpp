            cs->pub.sense == CONN_SENSE_WANT_WRITE ? APR_POLLOUT :
                    APR_POLLIN) | APR_POLLHUP | APR_POLLERR;
    cs->pub.sense = CONN_SENSE_DEFAULT;
    rv = apr_pollset_add(event_pollset, &cs->pfd);
    apr_thread_mutex_unlock(timeout_mutex);
    if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(03092)
                     "start_lingering_close: apr_pollset_add failure");
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_REMOVE(q, cs);
        apr_thread_mutex_unlock(timeout_mutex);
        apr_socket_close(cs->pfd.desc.s);
        ap_push_pool(worker_queue_info, cs->p);
