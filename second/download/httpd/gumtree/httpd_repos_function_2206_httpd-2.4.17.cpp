apr_status_t h2_tq_remove(h2_task_queue *q, struct h2_task *task)
{
    if (in_list(q, task)) {
        H2_TASK_REMOVE(task);
        return APR_SUCCESS;
    }
    return APR_NOTFOUND;
}