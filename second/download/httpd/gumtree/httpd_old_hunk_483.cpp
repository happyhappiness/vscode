    my_info->sd = 0;
    rv = apr_thread_create(&ts->listener, thread_attr, listener_thread,
                           my_info, pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "apr_thread_create: unable to create listener thread");
        /* In case system resources are maxxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again if we exit.
         * XXX Jeff doesn't see how Apache is going to try to fork again since
         * the exit code is APEXIT_CHILDFATAL
         */
        apr_sleep(apr_time_from_sec(10));
        clean_child_exit(APEXIT_CHILDFATAL);
    }
    apr_os_thread_get(&listener_os_thread, ts->listener);
}

/* XXX under some circumstances not understood, children can get stuck
 *     in start_threads forever trying to take over slots which will
