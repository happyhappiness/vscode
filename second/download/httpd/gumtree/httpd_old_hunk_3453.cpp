     * supposed to start up without the 1 second penalty between each fork.
     */
    remaining_children_to_start = ap_daemons_to_start;
    if (remaining_children_to_start > ap_daemons_limit) {
        remaining_children_to_start = ap_daemons_limit;
    }
    if (!is_graceful) {
        startup_children(remaining_children_to_start);
        remaining_children_to_start = 0;
    }
    else {
        /* give the system some time to recover before kicking into
            * exponential mode */
        hold_off_on_exponential_spawning = 10;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                "Server built: %s", ap_get_server_built());
    ap_log_command_line(plog, s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                "Accept mutex: %s (default: %s)",
                apr_proc_mutex_name(accept_mutex),
                apr_proc_mutex_defname());
    restart_pending = shutdown_pending = 0;
    mpm_state = AP_MPMQ_RUNNING;

    server_main_loop(remaining_children_to_start);
    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        ap_worker_pod_killpg(pod, ap_daemons_limit, FALSE);
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
        return DONE;
    } else if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
