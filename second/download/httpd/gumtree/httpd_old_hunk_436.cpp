        }
    }
    ap_max_daemons_limit = last_non_dead + 1;

    if (idle_thread_count > max_spare_threads) {
        /* Kill off one child */
        ap_mpm_pod_signal(pod, TRUE);
        idle_spawn_rate = 1;
    }
    else if (idle_thread_count < min_spare_threads) {
        /* terminate the free list */
        if (free_length == 0) {
            /* only report this condition once */
            static int reported = 0;
            
            if (!reported) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, 
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
            }
            if (idle_spawn_rate >= 8) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, 
                             ap_server_conf,
                             "server seems busy, (you may need "
                             "to increase StartServers, ThreadsPerChild "
                             "or Min/MaxSpareThreads), "
                             "spawning %d children, there are around %d idle "
                             "threads, and %d total children", free_length,
