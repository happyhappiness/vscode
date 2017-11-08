apr_status_t h2_mplx_create_task(h2_mplx *m, struct h2_stream *stream)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        conn_rec *c = h2_conn_create(m->c, stream->pool);
        stream->task = h2_task_create(m->id, stream->id, 
                                      stream->pool, m, c);
        
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}