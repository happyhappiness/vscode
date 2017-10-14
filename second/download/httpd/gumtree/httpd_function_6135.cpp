apr_status_t h2_task_do(h2_task *task, apr_thread_cond_t *cond)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(task);
    task->io = cond;
    task->input = h2_task_input_create(task, task->c);
    task->output = h2_task_output_create(task, task->c);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): process connection", task->id);
    ap_run_process_connection(task->c);
    
    if (task->frozen) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): process_conn returned frozen task", 
                      task->id);
        /* cleanup delayed */
        status = APR_EAGAIN;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
        status = APR_SUCCESS;
    }
    
    return status;
}