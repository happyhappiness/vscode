apr_status_t h2_task_freeze(h2_task *task)
{   
    if (!task->frozen) {
        task->frozen = 1;
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, 
                      "h2_task(%s), frozen", task->id);
    }
    return APR_SUCCESS;
}