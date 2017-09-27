        ap_add_input_filter("H2_TO_H1", NULL, NULL, c);
        ap_add_output_filter("H1_TO_H2", NULL, NULL, c);
    }
    return OK;
}

h2_task *h2_task_create(long session_id, const h2_request *req, 
                        conn_rec *c, h2_mplx *mplx)
{
    apr_pool_t *pool;
    h2_task *task;
    
    apr_pool_create(&pool, c->pool);
    task = apr_pcalloc(pool, sizeof(h2_task));
    if (task == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, c,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      session_id, req->id);
        h2_mplx_out_close(mplx, req->id);
        return NULL;
    }
    
    task->id          = apr_psprintf(pool, "%ld-%d", session_id, req->id);
    task->stream_id   = req->id;
    task->c           = c;
    task->mplx        = mplx;
    task->c->keepalives = mplx->c->keepalives;
    task->pool        = pool;
    task->request     = req;
    task->input_eos   = !req->body;
    task->ser_headers = req->serialize;
    task->blocking    = 1;

    h2_ctx_create_for(c, task);
    return task;
}

void h2_task_destroy(h2_task *task)
{
    if (task->pool) {
        apr_pool_destroy(task->pool);
    }
}

void h2_task_set_io_blocking(h2_task *task, int blocking)
{
    task->blocking = blocking;
}

apr_status_t h2_task_do(h2_task *task, apr_thread_cond_t *cond)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(task);
    task->io = cond;
    task->input = h2_task_input_create(task, task->c);
    task->output = h2_task_output_create(task, task->c);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): process connection", task->id);
    ap_run_process_connection(task->c);
    
    if (task->frozen) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): process_conn returned frozen task", 
                      task->id);
        /* cleanup delayed */
        status = APR_EAGAIN;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
        status = APR_SUCCESS;
    }
    
    return status;
}

static apr_status_t h2_task_process_request(h2_task *task, conn_rec *c)
{
    const h2_request *req = task->request;
    conn_state_t *cs = c->cs;
    request_rec *r;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  "h2_task(%s): create request_rec", task->id);
    r = h2_request_create_rec(req, c);
    if (r && (r->status == HTTP_OK)) {
        ap_update_child_status(c->sbh, SERVER_BUSY_READ, r);
        
        if (cs) {
            cs->state = CONN_STATE_HANDLER;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_task(%s): start process_request", task->id);
