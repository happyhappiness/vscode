ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                 "h2_workers: min=%d max=%d, mthrpchild=%d, idle_secs=%d", 
                 minw, maxw, max_threads_per_child, idle_secs);