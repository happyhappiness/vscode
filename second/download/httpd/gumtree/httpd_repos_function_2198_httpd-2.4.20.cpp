apr_status_t h2_task_output_write(h2_task_output *output,
                                  ap_filter_t* f, apr_bucket_brigade* bb)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    
    if (APR_BRIGADE_EMPTY(bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, output->task->c,
                      "h2_task(%s): empty write", output->task->id);
        return APR_SUCCESS;
    }
    
    if (output->task->frozen) {
        h2_util_bb_log(output->task->c, output->task->stream_id, APLOG_TRACE2,
                       "frozen task output write, ignored", bb);
        while (!APR_BRIGADE_EMPTY(bb)) {
            b = APR_BRIGADE_FIRST(bb);
            if (AP_BUCKET_IS_EOR(b)) {
                /* TODO: keep it */
                APR_BUCKET_REMOVE(b);
            }
            else {
                apr_bucket_delete(b);
            }
        }
        return APR_SUCCESS;
    }
    
    if (!output->response_open) {
        status = open_response(output, f, bb, "write");
        output->response_open = 1;
    }
    
    /* Attempt to write saved brigade first */
    if (status == APR_SUCCESS && output->bb && !APR_BRIGADE_EMPTY(output->bb)) {
        status = write_brigade_raw(output, f, output->bb);
    }
    
    /* If there is nothing saved (anymore), try to write the brigade passed */
    if (status == APR_SUCCESS
        && (!output->bb || APR_BRIGADE_EMPTY(output->bb))
        && !APR_BRIGADE_EMPTY(bb)) {
        status = write_brigade_raw(output, f, bb);
    }
    
    /* If the passed brigade is not empty, save it before return */
    if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, output->task->c,
                      "h2_task(%s): could not write all, saving brigade", 
                      output->task->id);
        if (!output->bb) {
            output->bb = apr_brigade_create(output->task->pool, output->task->c->bucket_alloc);
        }
        return ap_save_brigade(f, &output->bb, &bb, output->task->pool);
    }
    
    return status;
}