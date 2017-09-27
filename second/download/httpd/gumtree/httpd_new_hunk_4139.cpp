        /* Add work to pollset. */
        cs->pfd.reqevents = APR_POLLIN;
        rc = apr_pollset_add(event_pollset, &cs->pfd);
        apr_thread_mutex_unlock(timeout_mutex);

        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf, APLOGNO(03093)
                         "process_socket: apr_pollset_add failure");
            AP_DEBUG_ASSERT(rc == APR_SUCCESS);
        }
    }
    else if (cs->pub.state == CONN_STATE_SUSPENDED) {
        apr_atomic_inc32(&suspended_count);
