static apr_status_t output_write(h2_task *task, ap_filter_t* f, 
                                 apr_bucket_brigade* bb)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    int flush = 0;
    
    if (APR_BRIGADE_EMPTY(bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): empty write", task->id);
        return APR_SUCCESS;
    }
    
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
    
    if (!task->output.beam) {
        h2_beam_create(&task->output.beam, task->pool, 
                       task->stream_id, "output", 0); 
    }
    
    /* Attempt to write saved brigade first */
    if (task->output.bb && !APR_BRIGADE_EMPTY(task->output.bb)) {
        status = send_out(task, task->output.bb); 
        if (status != APR_SUCCESS) {
            return status;
        }
    }
    
    /* If there is nothing saved (anymore), try to write the brigade passed */
    if ((!task->output.bb || APR_BRIGADE_EMPTY(task->output.bb)) 
        && !APR_BRIGADE_EMPTY(bb)) {
        /* check if we have a flush before the end-of-request */
        if (!task->output.response_open) {
            for (b = APR_BRIGADE_FIRST(bb);
                 b != APR_BRIGADE_SENTINEL(bb);
                 b = APR_BUCKET_NEXT(b)) {
                if (AP_BUCKET_IS_EOR(b)) {
                    break;
                }
                else if (APR_BUCKET_IS_FLUSH(b)) {
                    flush = 1;
                }
            }
        }

        status = send_out(task, bb); 
        if (status != APR_SUCCESS) {
            return status;
        }
    }
    
    /* If the passed brigade is not empty, save it before return */
    if (!APR_BRIGADE_EMPTY(bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03405)
                      "h2_task(%s): could not write all, saving brigade", 
                      task->id);
        if (!task->output.bb) {
            task->output.bb = apr_brigade_create(task->pool, 
                                          task->c->bucket_alloc);
        }
        return ap_save_brigade(f, &task->output.bb, &bb, task->pool);
    }
    
    if (!task->output.response_open 
        && (flush || h2_beam_get_mem_used(task->output.beam) > (32*1024))) {
        /* if we have enough buffered or we got a flush bucket, open
        * the response now. */
        status = open_response(task);
        task->output.response_open = 1;
    }
    
    return status;
}