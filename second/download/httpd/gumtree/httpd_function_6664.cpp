static apr_status_t slave_out(h2_task *task, ap_filter_t* f, 
                              apr_bucket_brigade* bb)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    int flush = 0, blocking;
    
    if (task->frozen) {
        h2_util_bb_log(task->c, task->stream_id, APLOG_TRACE2,
                       "frozen task output write, ignored", bb);
        while (!APR_BRIGADE_EMPTY(bb)) {
            b = APR_BRIGADE_FIRST(bb);
            if (AP_BUCKET_IS_EOR(b)) {
                APR_BUCKET_REMOVE(b);
                task->eor = b;
            }
            else {
                apr_bucket_delete(b);
            }
        }
        return APR_SUCCESS;
    }

    /* we send block once we opened the output, so someone is there
     * reading it *and* the task is not assigned to a h2_req_engine */
    blocking = (!task->assigned && task->output.opened);
    if (!task->output.opened) {
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b)) {
            if (APR_BUCKET_IS_FLUSH(b)) {
                flush = 1;
                break;
            }
        }
    }
    
    if (task->output.bb && !APR_BRIGADE_EMPTY(task->output.bb)) {
        /* still have data buffered from previous attempt.
         * setaside and append new data and try to pass the complete data */
        if (!APR_BRIGADE_EMPTY(bb)) {
            status = ap_save_brigade(f, &task->output.bb, &bb, task->pool);
        }
        if (status == APR_SUCCESS) {
            status = send_out(task, task->output.bb, blocking);
        } 
    }
    else {
        /* no data buffered here, try to pass the brigade directly */
        status = send_out(task, bb, blocking); 
        if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
            /* could not write all, buffer the rest */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03405)
                          "h2_slave_out(%s): saving brigade", 
                          task->id);
            status = ap_save_brigade(f, &task->output.bb, &bb, task->pool);
            flush = 1;
        }
    }
    
    if (status == APR_SUCCESS && !task->output.opened && flush) {
        /* got a flush or could not write all, time to tell someone to read */
        status = open_output(task);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, task->c, 
                  "h2_slave_out(%s): slave_out leave", task->id);    
    return status;
}