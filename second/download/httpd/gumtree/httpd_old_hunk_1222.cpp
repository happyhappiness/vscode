        ap_mpm_pod_signal(pod, TRUE);
        idle_spawn_rate = 1;
    }
    else if (idle_thread_count < min_spare_threads) {
        /* terminate the free list */
        if (free_length == 0) {
            /* only report this condition once */
            static int reported = 0;

            if (!reported) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             ap_server_conf,
                             "server reached MaxClients setting, consider"
                             " raising the MaxClients setting");
                reported = 1;
            }
            idle_spawn_rate = 1;
        }
        else {
            if (free_length > idle_spawn_rate) {
                free_length = idle_spawn_rate;
