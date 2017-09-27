        /* cleanup pid file on normal shutdown */
        ap_remove_pid(pconf, ap_pid_fname);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00169)
                    "caught SIGTERM, shutting down");

        return DONE;
    }

    if (retained->mpm->shutdown_pending) {
        /* Time to perform a graceful shut down:
         * Reap the inactive children, and ask the active ones
         * to close their listeners, then wait until they are
         * all done to exit.
         */
        int active_children;
        apr_time_t cutoff = 0;

        /* Stop listening */
        ap_close_listeners();

        /* kill off the idle ones */
        for (i = 0; i < retained->mpm->num_buckets; i++) {
            ap_mpm_pod_killpg(all_buckets[i].pod, retained->max_daemons_limit);
        }

        /* Send SIGUSR1 to the active children */
        active_children = 0;
        for (index = 0; index < ap_daemons_limit; ++index) {
