h2_task *h2_task_create(long session_id,
                        int stream_id,
                        apr_pool_t *stream_pool,
                        h2_mplx *mplx, conn_rec *c)
{
    h2_task *task = apr_pcalloc(stream_pool, sizeof(h2_task));
    if (task == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, stream_pool,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      session_id, stream_id);
        h2_mplx_out_close(mplx, stream_id);
        return NULL;
    }
    
    APR_RING_ELEM_INIT(task, link);

    task->id = apr_psprintf(stream_pool, "%ld-%d", session_id, stream_id);
    task->stream_id = stream_id;
    task->mplx = mplx;
    
    task->c = c;
    
    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, stream_pool,
                  "h2_task(%s): created", task->id);
    return task;
}