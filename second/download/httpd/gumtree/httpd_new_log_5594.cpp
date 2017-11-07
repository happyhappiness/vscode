ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                         "h2_workers: got %d worker, adding 1", 
                         workers->worker_count);