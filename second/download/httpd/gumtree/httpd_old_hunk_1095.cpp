        ap_scoreboard_image->global->running_generation = ap_my_generation;

    	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
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
{
    int debug;
    char *addrname = NULL;

    debug = ap_exists_config_define("DEBUG");

    is_graceful = 0;
    ap_my_pid = getpid();
    addrname = getaddressspacename (NULL, NULL);
    if (addrname) {
