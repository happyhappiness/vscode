h2_task *h2_task_create(conn_rec *slave, int stream_id,
                        const h2_request *req, h2_mplx *m,
                        h2_bucket_beam *input, 
                        apr_interval_time_t timeout,
                        apr_size_t output_max_mem)
{
    apr_pool_t *pool;
    h2_task *task;
    
    ap_assert(slave);
    ap_assert(req);

    apr_pool_create(&pool, slave->pool);
    task = apr_pcalloc(pool, sizeof(h2_task));
    if (task == NULL) {
        return NULL;
    }
    task->id          = "000";
    task->stream_id   = stream_id;
    task->c           = slave;
    task->mplx        = m;
    task->pool        = pool;
    task->request     = req;
    task->timeout     = timeout;
    task->input.beam  = input;
    task->output.max_buffer = output_max_mem;

    return task;
}