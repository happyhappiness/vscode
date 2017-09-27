        if (APLOGctrace1(f->c)) {
            char buffer[1024];
            apr_size_t len = sizeof(buffer)-1;
            apr_brigade_flatten(bb, buffer, &len);
            buffer[len] = 0;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                          "h2_slave_in(%s): getline: %s",
                          task->id, buffer);
        }
    }
    else {
        /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
         * to support it. Seems to work. */
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                      APLOGNO(03472) 
                      "h2_slave_in(%s), unsupported READ mode %d", 
                      task->id, mode);
        status = APR_ENOTIMPL;
    }
    
    if (APLOGctrace1(f->c)) {
        apr_brigade_length(bb, 0, &bblen);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                      "h2_slave_in(%s): %ld data bytes", task->id, (long)bblen);
    }
    return status;
}

static apr_status_t h2_filter_slave_output(ap_filter_t* filter,
                                           apr_bucket_brigade* brigade)
{
    h2_task *task = h2_ctx_cget_task(filter->c);
    apr_status_t status;
    
    ap_assert(task);
    status = slave_out(task, filter, brigade);
    if (status != APR_SUCCESS) {
        h2_task_rst(task, H2_ERR_INTERNAL_ERROR);
    }
    return status;
}

static apr_status_t h2_filter_parse_h1(ap_filter_t* f, apr_bucket_brigade* bb)
{
    h2_task *task = h2_ctx_cget_task(f->c);
    apr_status_t status;
    
    ap_assert(task);
    /* There are cases where we need to parse a serialized http/1.1 
     * response. One example is a 100-continue answer in serialized mode
     * or via a mod_proxy setup */
    while (!task->output.sent_response) {
        status = h2_from_h1_parse_response(task, f, bb);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
                      "h2_task(%s): parsed response", task->id);
        if (APR_BRIGADE_EMPTY(bb) || status != APR_SUCCESS) {
            return status;
        }
    }
    
    return ap_pass_brigade(f->next, bb);
}

/*******************************************************************************
 * task things
 ******************************************************************************/
 
int h2_task_can_redo(h2_task *task) {
    if (h2_beam_was_received(task->input.beam)) {
        /* cannot repeat that. */
        return 0;
    }
    return (!strcmp("GET", task->request->method)
            || !strcmp("HEAD", task->request->method)
            || !strcmp("OPTIONS", task->request->method));
}

void h2_task_redo(h2_task *task)
{
    task->rst_error = 0;
}

void h2_task_rst(h2_task *task, int error)
{
    task->rst_error = error;
    h2_beam_abort(task->input.beam);
    if (!task->worker_done) {
        h2_beam_abort(task->output.beam);
    }
    if (task->c) {
        task->c->aborted = 1;
    }
}
