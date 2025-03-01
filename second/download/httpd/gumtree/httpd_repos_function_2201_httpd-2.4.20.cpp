h2_task_input *h2_task_input_create(h2_task *task, conn_rec *c)
{
    h2_task_input *input = apr_pcalloc(task->pool, sizeof(h2_task_input));
    if (input) {
        input->task = task;
        input->bb = NULL;
        input->block = APR_BLOCK_READ;
        
        if (task->ser_headers) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "h2_task_input(%s): serialize request %s %s", 
                          task->id, task->request->method, task->request->path);
            input->bb = apr_brigade_create(task->pool, c->bucket_alloc);
            apr_brigade_printf(input->bb, NULL, NULL, "%s %s HTTP/1.1\r\n", 
                               task->request->method, task->request->path);
            apr_table_do(ser_header, input, task->request->headers, NULL);
            apr_brigade_puts(input->bb, NULL, NULL, "\r\n");
            if (input->task->input_eos) {
                APR_BRIGADE_INSERT_TAIL(input->bb, apr_bucket_eos_create(c->bucket_alloc));
            }
        }
        else if (!input->task->input_eos) {
            input->bb = apr_brigade_create(task->pool, c->bucket_alloc);
        }
        else {
            /* We do not serialize and have eos already, no need to
             * create a bucket brigade. */
        }
    }
    return input;
}