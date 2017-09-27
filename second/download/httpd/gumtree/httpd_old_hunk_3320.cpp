         * listener_may_exit flag is clear and the time it enters a
         * blocking syscall, the signal didn't do any good...  work around
         * that by sleeping briefly and sending it again
         */

        iter = 0;
        while (iter < 10 &&
#ifdef HAVE_PTHREAD_KILL
               pthread_kill(*listener_os_thread, 0)
#else
               kill(ap_my_pid, 0)
#endif
               == 0) {
            /* listener not dead yet */
            apr_sleep(apr_time_make(0, 500000));
            wakeup_listener();
            ++iter;
        }
        if (iter >= 10) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                         "the listener thread didn't exit");
        }
        else {
            rv = apr_thread_join(&thread_rv, listener);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "apr_thread_join: unable to join listener thread");
            }
        }
    }

    for (i = 0; i < threads_per_child; i++) {
        if (threads[i]) {       /* if we ever created this thread */
            rv = apr_thread_join(&thread_rv, threads[i]);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "apr_thread_join: unable to join worker "
                             "thread %d", i);
            }
        }
    }
}
