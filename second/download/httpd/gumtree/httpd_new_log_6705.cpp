ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00486)
                             "server seems busy, (you may need "
                             "to increase StartServers, ThreadsPerChild "
                             "or Min/MaxSpareThreads), "
                             "spawning %d children, there are around %d idle "
                             "threads, %d active children, and %d children "
                             "that are shutting down", free_length,
                             idle_thread_count, active_daemons,
                             retained->total_daemons);