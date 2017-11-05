static apr_status_t get_mplx_next(h2_worker *worker, void *ctx, 
                                  h2_task **ptask, int *psticky)
{
    apr_status_t status;
    apr_time_t wait_until = 0, now;
    h2_workers *workers = ctx;
    h2_task *task = NULL;
    
    *ptask = NULL;
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
             * and we have still more workers, we shut down one after
             * the other. */
            cleanup_zombies(workers, 0);
            if (workers->worker_count > workers->min_workers) {
                now = apr_time_now();
                if (now >= wait_until) {
                    wait_until = now + apr_time_from_sec(workers->max_idle_secs);
                }
                
                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                             "h2_worker(%d): waiting signal, "
                             "workers=%d, idle=%d", worker->id, 
                             (int)workers->worker_count, 
                             workers->idle_workers);
                status = apr_thread_cond_timedwait(workers->mplx_added,
                                                   workers->lock, 
                                                   wait_until - now);
                if (status == APR_TIMEUP
                    && workers->worker_count > workers->min_workers) {
                    /* waited long enough without getting a task and
                     * we are above min workers, abort this one. */
                    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, 
                                 workers->s,
                                 "h2_workers: aborting idle worker");
                    h2_worker_abort(worker);
                    break;
                }
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                             "h2_worker(%d): waiting signal (eternal), "
                             "worker_count=%d, idle=%d", worker->id, 
                             (int)workers->worker_count,
                             workers->idle_workers);
                apr_thread_cond_wait(workers->mplx_added, workers->lock);
            }
        }
        
        /* Here, we either have gotten task or decided to shut down
         * the calling worker.
         */
        if (task) {
            /* Ok, we got something to give back to the worker for execution. 
             * If we have more idle workers than h2_mplx in our queue, then
             * we let the worker be sticky, e.g. making it poll the task's
             * h2_mplx instance for more work before asking back here.
             * This avoids entering our global lock as long as enough idle
             * workers remain. Stickiness of a worker ends when the connection
             * has no new tasks to process, so the worker will get back here
             * eventually.
             */
            *ptask = task;
            *psticky = (workers->max_workers >= workers->mplx_count);
            
            if (workers->mplx_count && workers->idle_workers > 1) {
                apr_thread_cond_signal(workers->mplx_added);
            }
        }
        
        --workers->idle_workers;
        apr_thread_mutex_unlock(workers->lock);
    }
    
    return *ptask? APR_SUCCESS : APR_EOF;
}