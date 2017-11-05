int h2_filter_h2_status_handler(request_rec *r)
{
    h2_ctx *ctx = h2_ctx_rget(r);
    conn_rec *c = r->connection;
    h2_task *task;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    apr_status_t status;
    
    if (strcmp(r->handler, "http2-status")) {
        return DECLINED;
    }
    if (r->method_number != M_GET && r->method_number != M_POST) {
        return DECLINED;
    }

    task = ctx? h2_ctx_get_task(ctx) : NULL;
    if (task) {

        if ((status = ap_discard_request_body(r)) != OK) {
            return status;
        }
        
        /* We need to handle the actual output on the main thread, as
         * we need to access h2_session information. */
        r->status = 200;
        r->clength = -1;
        r->chunked = 1;
        apr_table_unset(r->headers_out, "Content-Length");
        ap_set_content_type(r, "application/json");
        apr_table_setn(r->notes, H2_FILTER_DEBUG_NOTE, "on");

        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        b = h2_bucket_observer_create(c->bucket_alloc, status_event, task);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "status_handler(%s): checking for incoming trailers", 
                      task->id);
        if (r->trailers_in && !apr_is_empty_table(r->trailers_in)) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "status_handler(%s): seeing incoming trailers", 
                          task->id);
            apr_table_setn(r->trailers_out, "h2-trailers-in", 
                           apr_itoa(r->pool, 1));
        }
        
        status = ap_pass_brigade(r->output_filters, bb);
        if (status == APR_SUCCESS
            || r->status != HTTP_OK
            || c->aborted) {
            return OK;
        }
        else {
            /* no way to know what type of error occurred */
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, status, r,
                          "status_handler(%s): ap_pass_brigade failed", 
                          task->id);
            return AP_FILTER_ERROR;
        }
    }
    return DECLINED;
}