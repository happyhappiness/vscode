            display_settings();
        apr_thread_yield();
        apr_sleep(SCOREBOARD_MAINTENANCE_INTERVAL);
    }
    mpm_state = AP_MPMQ_STOPPING;

    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[0].pid,
                        ap_my_generation,
                        0,
                        MPM_CHILD_EXITED);

    /* Shutdown the listen sockets so that we don't get stuck in a blocking call.
    shutdown_listeners();*/

    if (shutdown_pending) { /* Got an unload from the console */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00226)
            "caught SIGTERM, shutting down");

        while (worker_thread_count > 0) {
            printf ("\rShutdown pending. Waiting for %d thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
