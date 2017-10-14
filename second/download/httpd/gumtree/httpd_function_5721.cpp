static int netware_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    apr_status_t status=0;

    pconf = _pconf;
    ap_server_conf = s;

    if (setup_listeners(s)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, status, s, APLOGNO(00223)
            "no listening sockets available, shutting down");
        return -1;
    }

    restart_pending = shutdown_pending = 0;
    worker_thread_count = 0;

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_NOT_SHARED) != OK) {
            return 1;
        }
    }

    /* Only set slot 0 since that is all NetWare will ever have. */
    ap_scoreboard_image->parent[0].pid = getpid();
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[0].pid,
                        ap_my_generation,
                        0,
                        MPM_CHILD_STARTED);

    set_signals();

    apr_pool_create(&pmain, pconf);
    ap_run_child_init(pmain, ap_server_conf);

    if (ap_threads_max_free < ap_threads_min_free + 1)  /* Don't thrash... */
        ap_threads_max_free = ap_threads_min_free + 1;
    request_count = 0;

    startup_workers(ap_threads_to_start);

     /* Allow the Apache screen to be closed normally on exit() only if it
        has not been explicitly forced to close on exit(). (ie. the -E flag
        was specified at startup) */
    if (hold_screen_on_exit > 0) {
        hold_screen_on_exit = 0;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00224)
            "%s configured -- resuming normal operations",
            ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00225)
            "Server built: %s", ap_get_server_built());
    ap_log_command_line(plog, s);
    show_server_data();

    mpm_state = AP_MPMQ_RUNNING;
    while (!restart_pending && !shutdown_pending) {
        perform_idle_server_maintenance(pconf);
        if (show_settings)
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
            printf ("\rShutdown pending. Waiting for %u thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }

        mpm_main_cleanup();
        return 1;
    }
    else {  /* the only other way out is a restart */
        /* advance to the next generation */
        /* XXX: we really need to make sure this new generation number isn't in
         * use by any of the children.
         */
        ++ap_my_generation;
        ap_scoreboard_image->global->running_generation = ap_my_generation;

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00227)
                "Graceful restart requested, doing restart");

        /* Wait for all of the threads to terminate before initiating the restart */
        while (worker_thread_count > 0) {
            printf ("\rRestart pending. Waiting for %u thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }
        printf ("\nRestarting...\n");
    }

    mpm_main_cleanup();
    return 0;
}