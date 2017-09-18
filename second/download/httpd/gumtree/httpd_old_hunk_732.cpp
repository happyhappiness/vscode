            listener_started = 1;
        }
        if (start_thread_may_exit || threads_created == ap_threads_per_child) {
            break;
        }
        /* wait for previous generation to clean up an entry */
        apr_sleep(1 * APR_USEC_PER_SEC);
        ++loops;
        if (loops % 120 == 0) { /* every couple of minutes */
            if (prev_threads_created == threads_created) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             "child %" APR_PID_T_FMT " isn't taking over "
                             "slots very quickly (%d of %d)",
