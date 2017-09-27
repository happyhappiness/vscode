    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00292)
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00293)
                "Server built: %s", ap_get_server_built());
    ap_log_command_line(plog, s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00294)
                "Accept mutex: %s (default: %s)",
                apr_proc_mutex_name(accept_mutex),
                apr_proc_mutex_defname());
    mpm_state = AP_MPMQ_RUNNING;

    server_main_loop(remaining_children_to_start);
    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !retained->is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        ap_mpm_podx_killpg(pod, ap_daemons_limit, AP_MPM_PODX_RESTART);
        ap_reclaim_child_processes(1, /* Start with SIGTERM */
                                   worker_note_child_killed);

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            ap_remove_pid(pconf, ap_pid_fname);
