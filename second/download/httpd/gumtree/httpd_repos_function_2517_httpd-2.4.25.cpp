void h2_task_destroy(h2_task *task)
{
    if (task->eor) {
        apr_bucket_destroy(task->eor);
    }
    if (task->pool) {
        apr_pool_destroy(task->pool);
    }
}