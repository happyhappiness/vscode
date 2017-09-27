{
    if (task->frozen) {
        task->frozen = 0;
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03407) 
                      "h2_task(%s), thawed", task->id);
    }
    task->detached = 1;
    return APR_SUCCESS;
}

int h2_task_is_detached(h2_task *task)
{
    return task->detached;
}
