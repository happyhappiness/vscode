        ap_mpm_pod_signal(pod, TRUE);
        idle_spawn_rate = 1;
    }
    else if (idle_thread_count < min_spare_threads) {
        /* terminate the free list */
        if (free_length == 0) {
            /* No room for more children, might warn about configuration */
            if (active_thread_count >= ap_daemons_limit * ap_threads_per_child) {
                /* no threads are "inactive" - starting, stopping, etc. - which would confuse matters */
                /* Are all threads in use?  Then we're really at MaxClients */
                if (0 == idle_thread_count) {
                    /* only report this condition once */
                    static int reported = 0;

                    if (!reported) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     ap_server_conf,
                                     "server reached MaxClients setting, consider"
                                     " raising the MaxClients setting");
                        reported = 1;
                    }
                } else {
                    static int reported = 0;

                    if (!reported) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     ap_server_conf,
                                     "server is within MinSpareThreads of MaxClients, consider"
                                     " raising the MaxClients setting");
                        reported = 1;
                    }
                }
            }
            idle_spawn_rate = 1;
        }
        else {
            if (free_length > idle_spawn_rate) {
                free_length = idle_spawn_rate;
