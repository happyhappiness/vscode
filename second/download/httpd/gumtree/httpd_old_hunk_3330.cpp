        int index;
        apr_time_t cutoff = 0;

        /* Close our listeners, and then ask our children to do same */
        ap_close_listeners();
        ap_event_pod_killpg(pod, ap_daemons_limit, TRUE);
        ap_relieve_child_processes();

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            const char *pidfile = NULL;
            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
            if ( pidfile != NULL && unlink(pidfile) == 0)
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%ld)",
                             pidfile, (long)getpid());

            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "caught " AP_SIG_GRACEFUL_STOP_STRING
                         ", shutting down gracefully");
        }

        if (ap_graceful_shutdown_timeout) {
            cutoff = apr_time_now() +
