static apr_status_t get_mplx_next(h2_worker *worker, h2_mplx **pm, 
                                  h2_task **ptask, void *ctx)
{
    apr_status_t status;
    h2_mplx *m = NULL;
    h2_task *task = NULL;
    apr_time_t max_wait, start_wait;
    int has_more = 0;
    h2_workers *workers = (h2_workers *)ctx;
    
    if (*pm && ptask != NULL) {
        /* We have a h2_mplx instance and the worker wants the next task. 
         * Try to get one from the given mplx. */
        *ptask = h2_mplx_pop_task(*pm, worker, &has_more);
        if (*ptask) {
            return APR_SUCCESS;
        }
    }
    
    if (*pm) {
        /* Got a mplx handed in, but did not get or want a task from it. 
         * Release it, as the workers reference will be wiped.
         */
        h2_mplx_release(*pm);
        *pm = NULL;
    }
    
    if (!ptask) {
        /* the worker does not want a next task, we're done.
         */
        return APR_SUCCESS;
    }
    
    max_wait = apr_time_from_sec(apr_atomic_read32(&workers->max_idle_secs));
    start_wait = apr_time_now();
    
    status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ++workers->idle_worker_count;
        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                     "h2_worker(%d): looking for work", h2_worker_get_id(worker));
        
        while (!task && !h2_worker_is_aborted(worker) && !workers->aborted) {
            
            /* Get the next h2_mplx to process that has a task to hand out.
             * If it does, place it at the end of the queu and return the
             * task to the worker.
             * If it (currently) has no tasks, remove it so that it needs
             * to register again for scheduling.
             * If we run out of h2_mplx in the queue, we need to wait for
             * new mplx to arrive. Depending on how many workers do exist,
             * we do a timed wait or block indefinitely.
             */
            m = NULL;
            while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
                m = H2_MPLX_LIST_FIRST(&workers->mplxs);
                H2_MPLX_REMOVE(m);
                
                task = h2_mplx_pop_task(m, worker, &has_more);
                if (task) {
                    if (has_more) {
                        H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
                    }
                    else {
                        has_more = !H2_MPLX_LIST_EMPTY(&workers->mplxs);
                    }
                    break;
                }
            }
            
            if (!task) {
                /* Need to wait for either a new mplx to arrive.
                 */
                cleanup_zombies(workers, 0);
                
                if (workers->worker_count > workers->min_size) {
                    apr_time_t now = apr_time_now();
                    if (now >= (start_wait + max_wait)) {
                        /* waited long enough without getting a task. */
                        if (workers->worker_count > workers->min_size) {
                            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, 
                                         workers->s,
                                         "h2_workers: aborting idle worker");
                            h2_worker_abort(worker);
                            break;
                        }
                    }
                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                                 "h2_worker(%d): waiting signal, "
                                 "worker_count=%d", worker->id, 
                                 (int)workers->worker_count);
                    apr_thread_cond_timedwait(workers->mplx_added,
                                              workers->lock, max_wait);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                                 "h2_worker(%d): waiting signal (eternal), "
                                 "worker_count=%d", worker->id, 
                                 (int)workers->worker_count);
                    apr_thread_cond_wait(workers->mplx_added, workers->lock);
                }
            }
        }
        
        /* Here, we either have gotten task and mplx for the worker or
         * needed to give up with more than enough workers.
         */
        if (task) {
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                         "h2_worker(%d): start task(%s)",
                         h2_worker_get_id(worker), task->id);
            /* Since we hand out a reference to the worker, we increase
             * its ref count.
             */
            h2_mplx_reference(m);
            *pm = m;
            *ptask = task;
            
            if (has_more && workers->idle_worker_count > 1) {
                apr_thread_cond_signal(workers->mplx_added);
            }
            status = APR_SUCCESS;
        }
        else {
            status = APR_EOF;
        }
        
        --workers->idle_worker_count;
        apr_thread_mutex_unlock(workers->lock);
    }
    
    return status;
}