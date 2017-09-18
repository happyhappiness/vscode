               pthread_kill(*listener_os_thread, 0)
#else
               kill(ap_my_pid, 0)
#endif
               == 0) {
            /* listener not dead yet */
            apr_sleep(APR_USEC_PER_SEC / 2);
            wakeup_listener();
            ++iter;
        }
        if (iter >= 10) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "the listener thread didn't exit");
