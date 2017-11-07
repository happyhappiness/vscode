apr_status_t h2_task_do(h2_task *task, apr_thread_t *thread)
{
    AP_DEBUG_ASSERT(task);
    
    task->input.block = APR_BLOCK_READ;
    task->input.chunked = task->request->chunked;
    task->input.eos = !task->request->body;
    if (task->input.eos && !task->input.chunked && !task->ser_headers) {
        /* We do not serialize/chunk and have eos already, no need to
         * create a bucket brigade. */
        task->input.bb = NULL;
        task->input.eos_written = 1;
    }
    else {
        task->input.bb = apr_brigade_create(task->pool, task->c->bucket_alloc);
        if (task->ser_headers) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                          "h2_task(%s): serialize request %s %s", 
                          task->id, task->request->method, task->request->path);
            apr_brigade_printf(task->input.bb, NULL, 
                               NULL, "%s %s HTTP/1.1\r\n", 
                               task->request->method, task->request->path);
            apr_table_do(input_ser_header, task, task->request->headers, NULL);
            apr_brigade_puts(task->input.bb, NULL, NULL, "\r\n");
        }
        if (task->input.eos) {
            input_append_eos(task, NULL);
        }
    }
    
    task->output.from_h1 = h2_from_h1_create(task->stream_id, task->pool);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): process connection", task->id);
    task->c->current_thread = thread; 
    ap_run_process_connection(task->c);
    
    if (task->frozen) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): process_conn returned frozen task", 
                      task->id);
        /* cleanup delayed */
        return APR_EAGAIN;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
        return output_finish(task);
    }
}