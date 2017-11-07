h2_task *h2_task_create(conn_rec *c, int stream_id, const h2_request *req, 
                        h2_bucket_beam *input, h2_bucket_beam *output,  
                        h2_mplx *mplx)
{
    apr_pool_t *pool;
    h2_task *task;
    
    ap_assert(mplx);
    ap_assert(c);
    ap_assert(req);

    apr_pool_create(&pool, c->pool);
    task = apr_pcalloc(pool, sizeof(h2_task));
    if (task == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, c,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      c->id, stream_id);
        return NULL;
    }
    task->id          = apr_psprintf(pool, "%ld-%d", c->master->id, stream_id);
    task->stream_id   = stream_id;
    task->c           = c;
    task->mplx        = mplx;
    task->c->keepalives = mplx->c->keepalives;
    task->pool        = pool;
    task->request     = req;
    task->input.beam  = input;
    task->output.beam = output;
    
    apr_thread_cond_create(&task->cond, pool);

    h2_ctx_create_for(c, task);
    return task;
}