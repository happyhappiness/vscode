static void* APR_THREAD_FUNC execute(apr_thread_t *thread, void *wctx)
{
    h2_worker *worker = (h2_worker *)wctx;
    int sticky;
    
    while (!worker->aborted) {
        h2_task *task;
        
        /* Get a h2_task from the main workers queue. */
        worker->get_next(worker, worker->ctx, &task, &sticky);
        while (task) {
            h2_task_do(task, worker->io);
            
            /* if someone was waiting on this task, time to wake up */
            apr_thread_cond_signal(worker->io);
            /* report the task done and maybe get another one from the same
             * mplx (= master connection), if we can be sticky. 
             */
            if (sticky && !worker->aborted) {
                h2_mplx_task_done(task->mplx, task, &task);
            }
            else {
                h2_mplx_task_done(task->mplx, task, NULL);
                task = NULL;
            }
        }
    }

    worker->worker_done(worker, worker->ctx);
    return NULL;
}