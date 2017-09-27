    
    ctx = h2_ctx_get(c, 0);
    (void)arg;
    if (h2_ctx_is_task(ctx)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "h2_h2, pre_connection, found stream task");
        
        /* Add our own, network level in- and output filters.
         */
        ap_add_input_filter("H2_TO_H1", NULL, NULL, c);
        ap_add_output_filter("H1_TO_H2", NULL, NULL, c);
    }
    return OK;
}

h2_task *h2_task_create(conn_rec *c, const h2_request *req, 
                        h2_bucket_beam *input, h2_mplx *mplx)
{
    apr_pool_t *pool;
    h2_task *task;
    
    apr_pool_create(&pool, c->pool);
    task = apr_pcalloc(pool, sizeof(h2_task));
    if (task == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, c,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      c->id, req->id);
        return NULL;
    }
    
    task->id          = apr_psprintf(pool, "%ld-%d", c->id, req->id);
    task->stream_id   = req->id;
    task->c           = c;
    task->mplx        = mplx;
    task->c->keepalives = mplx->c->keepalives;
    task->pool        = pool;
    task->request     = req;
    task->ser_headers = req->serialize;
    task->blocking    = 1;
    task->input.beam  = input;
    
    apr_thread_cond_create(&task->cond, pool);

    h2_ctx_create_for(c, task);
    return task;
}

void h2_task_destroy(h2_task *task)
{
    if (task->output.beam) {
        h2_beam_destroy(task->output.beam);
        task->output.beam = NULL;
    }
    if (task->eor) {
        apr_bucket_destroy(task->eor);
    }
    if (task->pool) {
        apr_pool_destroy(task->pool);
    }
}

void h2_task_set_io_blocking(h2_task *task, int blocking)
{
    task->blocking = blocking;
}

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
    
