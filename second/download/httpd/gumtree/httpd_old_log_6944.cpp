ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                             "h2_worker(%d): waiting signal, "
                             "workers=%d, idle=%d", worker->id, 
                             (int)workers->worker_count, 
                             workers->idle_workers);