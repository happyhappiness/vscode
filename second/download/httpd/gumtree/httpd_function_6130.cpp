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