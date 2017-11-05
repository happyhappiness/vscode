int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    apr_status_t status=0;

    pconf = _pconf;
    ap_server_conf = s;

    if (setup_listeners(s)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, status, s,
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

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
            "%s configured -- resuming normal operations",
            ap_get_server_version());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
            "Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
            "AcceptMutex: %s (default: %s)",
            apr_proc_mutex_name(accept_mutex),
            apr_proc_mutex_defname());
#endif
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


    /* Shutdown the listen sockets so that we don't get stuck in a blocking call.
    shutdown_listeners();*/

    if (shutdown_pending) { /* Got an unload from the console */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
            "caught SIGTERM, shutting down");

        while (worker_thread_count > 0) {
            printf ("\rShutdown pending. Waiting for %d thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }

        return 1;
    }
    else {  /* the only other way out is a restart */
        /* advance to the next generation */
        /* XXX: we really need to make sure this new generation number isn't in
         * use by any of the children.
         */
        ++ap_my_generation;
        ap_scoreboard_image->global->running_generation = ap_my_generation;

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "Graceful restart requested, doing restart");

        /* Wait for all of the threads to terminate before initiating the restart */
        while (worker_thread_count > 0) {
            printf ("\rRestart pending. Waiting for %d thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }
        printf ("\nRestarting...\n");
    }

    return 0;
}