    else {
        /* give the system some time to recover before kicking into
            * exponential mode */
        hold_off_on_exponential_spawning = 10;
    }

    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_version());
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, ap_server_conf,
                "Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, ap_server_conf,
		"AcceptMutex: %s", ap_valid_accept_mutex_string);
#endif
    restart_pending = shutdown_pending = 0;

    server_main_loop(remaining_children_to_start);

    if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         * (By "gracefully" we don't mean graceful in the same sense as 
         * "apachectl graceful" where we allow old connections to finish.)
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, FALSE);
        ap_reclaim_child_processes(1);                /* Start with SIGTERM */

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            const char *pidfile = NULL;
            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
            if ( pidfile != NULL && unlink(pidfile) == 0)
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%ld)",
                             pidfile, (long)getpid());
    
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0,
                         ap_server_conf, "caught SIGTERM, shutting down");
        }
        return 1;
    }

    /* we've been told to restart */
