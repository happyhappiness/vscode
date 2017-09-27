ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                 "h2_workers: min=%d max=%d, mthrpchild=%d, tx_files=%d", 
                 minw, maxw, max_threads_per_child, max_tx_handles);