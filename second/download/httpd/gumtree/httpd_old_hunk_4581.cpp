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
