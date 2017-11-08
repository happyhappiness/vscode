void h2_worker_release_task(h2_worker *worker, struct h2_task *task)
{
    task->io = NULL;
    task->pool = NULL;
    apr_pool_clear(worker->task_pool);
}