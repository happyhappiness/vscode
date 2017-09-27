ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "h2_workers: min=%d max=%d, mthrpchild=%d, thr_limit=%d", 
                 minw, maxw, max_threads_per_child, threads_limit);