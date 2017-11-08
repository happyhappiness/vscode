void h2_task_destroy(h2_task *task)
{
    if (task->pool) {
        apr_pool_destroy(task->pool);
    }
}