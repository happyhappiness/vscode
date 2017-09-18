

    /* Shutdown the listen sockets so that we don't get stuck in a blocking call. 
    shutdown_listeners();*/

    if (shutdown_pending) { /* Got an unload from the console */
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
            "caught SIGTERM, shutting down");

        DBPRINT0 ("Shutdown pending. Waiting for threads to terminate...\n");
        while (worker_thread_count > 0)
            apr_thread_yield();

        return 1;
    }
    else {  /* the only other way out is a restart */
        /* advance to the next generation */
        /* XXX: we really need to make sure this new generation number isn't in
         * use by any of the children.
         */
        ++ap_my_generation;
        ap_scoreboard_image->global->running_generation = ap_my_generation;

    	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
		    "Graceful restart requested, doing restart");

        /* Wait for all of the threads to terminate before initiating the restart */
        DBPRINT0 ("Restart pending. Waiting for threads to terminate...\n");
        while (worker_thread_count > 0) {
            apr_thread_yield();
        }
        DBPRINT0 ("restarting...\n");
    }

    return 0;
}

static int netware_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
