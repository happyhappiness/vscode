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
