h2_task *h2_worker_create_task(h2_worker *worker, h2_mplx *m, 
                               const h2_request *req, int eos)
{
    h2_task *task;
    
    /* Create a subpool from the worker one to be used for all things
     * with life-time of this task execution.
     */
    if (!worker->task_pool) {
        apr_pool_create(&worker->task_pool, worker->pool);
    }
    task = h2_task_create(m->id, req, worker->task_pool, m, eos);
    
    /* Link the task to the worker which provides useful things such
     * as mutex, a socket etc. */
    task->io = worker->io;
    
    return task;
}