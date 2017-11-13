apr_status_t h2_task_thaw(h2_task *task)
{
    if (task->frozen) {
        task->frozen = 0;
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, 
                      "h2_task(%s), thawed", task->id);
    }
    task->detached = 1;
    return APR_SUCCESS;
}