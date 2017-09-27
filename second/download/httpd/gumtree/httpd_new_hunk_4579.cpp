        else if (APR_STATUS_IS_EOF(status)) {
            break;
        }
        else if (status != APR_SUCCESS) {
            return status;
        }

        if (trace1) {
            h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                        "input.beam recv raw", task->input.bb);
        }
        if (h2_task_logio_add_bytes_in) {
            apr_brigade_length(bb, 0, &bblen);
            h2_task_logio_add_bytes_in(f->c, bblen);
        }
    }
    
    /* Nothing there, no more data to get. Return APR_EAGAIN on
     * speculative reads, this is ap_check_pipeline()'s trick to
     * see if the connection needs closing. */
    if (status == APR_EOF && APR_BRIGADE_EMPTY(task->input.bb)) {
        return (mode == AP_MODE_SPECULATIVE)? APR_EAGAIN : APR_EOF;
    }

    if (trace1) {
        h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                    "task_input.bb", task->input.bb);
    }
           
    if (APR_BRIGADE_EMPTY(task->input.bb)) {
        if (trace1) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                          "h2_slave_in(%s): no data", task->id);
        }
        return (block == APR_NONBLOCK_READ)? APR_EAGAIN : APR_EOF;
    }
    
    if (mode == AP_MODE_EXHAUSTIVE) {
        /* return all we have */
        APR_BRIGADE_CONCAT(bb, task->input.bb);
