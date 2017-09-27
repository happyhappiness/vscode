    *psticky = 0;
    
    status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ++workers->idle_workers;
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                     "h2_worker(%d): looking for work", h2_worker_get_id(worker));
        
        while (!h2_worker_is_aborted(worker) && !workers->aborted
               && !(task = next_task(workers))) {
        
            /* Need to wait for a new tasks to arrive. If we are above
             * minimum workers, we do a timed wait. When timeout occurs
