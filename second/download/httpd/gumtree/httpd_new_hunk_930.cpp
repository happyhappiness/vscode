		"AcceptMutex: %s (default: %s)",
		apr_proc_mutex_name(accept_mutex),
		apr_proc_mutex_defname());
#endif
    restart_pending = shutdown_pending = 0;
    mpm_state = AP_MPMQ_RUNNING;

    server_main_loop(remaining_children_to_start);
    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, FALSE);
        ap_reclaim_child_processes(1);                /* Start with SIGTERM */

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            const char *pidfile = NULL;
            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
            if ( pidfile != NULL && unlink(pidfile) == 0)
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%" APR_PID_T_FMT ")",
                             pidfile, getpid());

            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                         ap_server_conf, "caught SIGTERM, shutting down");
        }
        return 1;
    } else if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        int active_children;
        int index;
        apr_time_t cutoff = 0;

        /* Close our listeners, and then ask our children to do same */
        ap_close_listeners();
        ap_mpm_pod_killpg(pod, ap_daemons_limit, TRUE);
        ap_relieve_child_processes();

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            const char *pidfile = NULL;
            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
            if ( pidfile != NULL && unlink(pidfile) == 0)
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%" APR_PID_T_FMT ")",
                             pidfile, getpid());

            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                         ap_server_conf, "caught SIGTERM, shutting down");
        }

        /* Don't really exit until each child has finished */
        shutdown_pending = 0;
        do {
            /* Pause for a second */
            apr_sleep(apr_time_from_sec(1));

            /* Relieve any children which have now exited */
            ap_relieve_child_processes();

            active_children = 0;
            for (index = 0; index < ap_daemons_limit; ++index) {
                if (MPM_CHILD_PID(index) != 0) {
                    if (kill(MPM_CHILD_PID(index), 0) == 0) {
                            active_children = 1;
                            /* Having just one child is enough to stay around */
                            break;
                    }
                }
            }
        } while (!shutdown_pending && active_children &&
                 (!ap_graceful_shutdown_timeout || apr_time_now() < cutoff));

        /* We might be here because we received SIGTERM, either
         * way, try and make sure that all of our processes are
         * really dead.
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, FALSE);
        ap_reclaim_child_processes(1);

        return 1;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);

    if (one_process) {
