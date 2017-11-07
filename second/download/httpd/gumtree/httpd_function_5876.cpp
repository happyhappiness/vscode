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