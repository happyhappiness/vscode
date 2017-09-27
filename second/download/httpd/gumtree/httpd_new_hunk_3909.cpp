    ap_register_input_filter("H2_TO_H1", h2_filter_stream_input,
                             NULL, AP_FTYPE_NETWORK);
    ap_register_output_filter("H1_TO_H2", h2_filter_stream_output,
                              NULL, AP_FTYPE_NETWORK);
    ap_register_output_filter("H1_TO_H2_RESP", h2_filter_read_response,
                              NULL, AP_FTYPE_PROTOCOL);
    ap_register_output_filter("H2_TRAILERS", h2_response_trailers_filter,
                              NULL, AP_FTYPE_PROTOCOL);
}

static int h2_task_pre_conn(conn_rec* c, void *arg)
{
    
    h2_ctx *ctx = h2_ctx_get(c);
    
    (void)arg;
    if (h2_ctx_is_task(ctx)) {
        h2_task *task = h2_ctx_get_task(ctx);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "h2_h2, pre_connection, found stream task");
        
        /* Add our own, network level in- and output filters.
         */
        ap_add_input_filter("H2_TO_H1", task, NULL, c);
        ap_add_output_filter("H1_TO_H2", task, NULL, c);
    }
    return OK;
}

h2_task *h2_task_create(long session_id, const h2_request *req, 
                        apr_pool_t *pool, h2_mplx *mplx, int eos)
{
    h2_task *task = apr_pcalloc(pool, sizeof(h2_task));
    if (task == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, pool,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      session_id, req->id);
        h2_mplx_out_close(mplx, req->id, NULL);
        return NULL;
    }
    
    task->id        = apr_psprintf(pool, "%ld-%d", session_id, req->id);
    task->stream_id = req->id;
    task->pool      = pool;
    task->mplx      = mplx;
    task->c         = h2_conn_create(mplx->c, task->pool);

    task->request   = req;
    task->input_eos = eos;    
    
    return task;
}

apr_status_t h2_task_destroy(h2_task *task)
{
    (void)task;
    return APR_SUCCESS;
}

apr_status_t h2_task_do(h2_task *task, h2_worker *worker)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(task);
    
    task->serialize_headers = h2_config_geti(task->request->config, H2_CONF_SER_HEADERS);

    status = h2_worker_setup_task(worker, task);
    
    /* save in connection that this one is a pseudo connection */
    h2_ctx_create_for(task->c, task);

    if (status == APR_SUCCESS) {
        task->input = h2_task_input_create(task, task->pool, 
                                           task->c->bucket_alloc);
        task->output = h2_task_output_create(task, task->pool);
        
        ap_process_connection(task->c, h2_worker_get_socket(worker));
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, task->c,
                      APLOGNO(02957) "h2_task(%s): error setting up h2_task", 
                      task->id);
    }
    
    if (task->input) {
        h2_task_input_destroy(task->input);
        task->input = NULL;
    }
    
    if (task->output) {
        h2_task_output_close(task->output);
        h2_task_output_destroy(task->output);
        task->output = NULL;
    }

    if (task->io) {
        apr_thread_cond_signal(task->io);
    }
    
    h2_worker_release_task(worker, task);
    h2_mplx_task_done(task->mplx, task->stream_id);
    
    return status;
}

static apr_status_t h2_task_process_request(const h2_request *req, conn_rec *c)
{
    request_rec *r;
    conn_state_t *cs = c->cs;

    r = h2_request_create_rec(req, c);
    if (r && (r->status == HTTP_OK)) {
        ap_update_child_status(c->sbh, SERVER_BUSY_READ, r);
        
        if (cs)
            cs->state = CONN_STATE_HANDLER;
        ap_process_request(r);
