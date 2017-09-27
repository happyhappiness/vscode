            return 1;
        }
    }
    return 0;
}

static void cleanup_zombies(h2_workers *workers, int lock)
{
    if (lock) {
        apr_thread_mutex_lock(workers->lock);
    }
    while (!H2_WORKER_LIST_EMPTY(&workers->zombies)) {
        h2_worker *zombie = H2_WORKER_LIST_FIRST(&workers->zombies);
        H2_WORKER_REMOVE(zombie);
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                      "h2_workers: cleanup zombie %d", zombie->id);
        h2_worker_destroy(zombie);
    }
    if (lock) {
        apr_thread_mutex_unlock(workers->lock);
    }
}

static h2_task *next_task(h2_workers *workers)
{
    h2_task *task = NULL;
    h2_mplx *last = NULL;
    int has_more;
    
    /* Get the next h2_mplx to process that has a task to hand out.
     * If it does, place it at the end of the queu and return the
     * task to the worker.
     * If it (currently) has no tasks, remove it so that it needs
     * to register again for scheduling.
     * If we run out of h2_mplx in the queue, we need to wait for
     * new mplx to arrive. Depending on how many workers do exist,
     * we do a timed wait or block indefinitely.
     */
    while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
        h2_mplx *m = H2_MPLX_LIST_FIRST(&workers->mplxs);
        
        if (last == m) {
            break;
        }
        H2_MPLX_REMOVE(m);
        --workers->mplx_count;
        
        task = h2_mplx_pop_task(m, &has_more);
        if (has_more) {
            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
            ++workers->mplx_count;
            if (!last) {
                last = m;
            }
        }
    }
    return task;
}

/**
 * Get the next task for the given worker. Will block until a task arrives
 * or the max_wait timer expires and more than min workers exist.
 */
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

static void worker_done(h2_worker *worker, void *ctx)
{
    h2_workers *workers = ctx;
    apr_status_t status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                     "h2_worker(%d): done", h2_worker_get_id(worker));
        H2_WORKER_REMOVE(worker);
        --workers->worker_count;
        H2_WORKER_LIST_INSERT_TAIL(&workers->zombies, worker);
        
        apr_thread_mutex_unlock(workers->lock);
