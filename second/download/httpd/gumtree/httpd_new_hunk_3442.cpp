            /* listener not dead yet */
            apr_sleep(apr_time_make(0, 500000));
            wakeup_listener();
            ++iter;
        }
        if (iter >= 10) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00276)
                         "the listener thread didn't exit");
        }
        else {
            rv = apr_thread_join(&thread_rv, listener);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00277)
                             "apr_thread_join: unable to join listener thread");
            }
        }
    }

    for (i = 0; i < threads_per_child; i++) {
