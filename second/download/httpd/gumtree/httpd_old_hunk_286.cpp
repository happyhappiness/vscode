            /* listener not dead yet */
            apr_sleep(APR_USEC_PER_SEC / 2);
            wakeup_listener();
            ++iter;
        }
        if (iter >= 10) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "the listener thread didn't exit");
        }
        else {
            rv = apr_thread_join(&thread_rv, listener);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
