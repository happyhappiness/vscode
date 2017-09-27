ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, workers->s,
                     "h2_workers: reserved %d tx handles, %d/%d left", 
                     (int)count, (int)workers->spare_tx_handles,
                     (int)workers->max_tx_handles);