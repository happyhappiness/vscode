        else if (APR_STATUS_IS_EOF(status)) {
            break;
        }
        else if (status != APR_SUCCESS) {
            return status;
        }
        
        h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                       "input.beam recv raw", task->input.bb);
        if (h2_task_logio_add_bytes_in) {
            apr_brigade_length(bb, 0, &bblen);
            h2_task_logio_add_bytes_in(f->c, bblen);
        }
    }
    
    /* Inspect the buckets received, detect EOS and apply
     * chunked encoding if necessary */
    if (status == APR_EOF && APR_BRIGADE_EMPTY(task->input.bb)) {
        return APR_EOF;
    }

    h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                   "task_input.bb", task->input.bb);
           
    if (APR_BRIGADE_EMPTY(task->input.bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_slave_in(%s): no data", task->id);
        return (block == APR_NONBLOCK_READ)? APR_EAGAIN : APR_EOF;
    }
    
    if (mode == AP_MODE_EXHAUSTIVE) {
        /* return all we have */
        APR_BRIGADE_CONCAT(bb, task->input.bb);
