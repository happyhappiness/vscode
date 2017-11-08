h2_stream *h2_mplx_open_io(h2_mplx *m, int stream_id)
{
    h2_stream *stream = NULL;
    apr_status_t status; 
    h2_io *io;

    if (m->aborted) {
        return NULL;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        apr_pool_t *stream_pool = m->spare_pool;
        
        if (!stream_pool) {
            apr_pool_create(&stream_pool, m->pool);
        }
        else {
            m->spare_pool = NULL;
        }
        
        stream = h2_stream_create(stream_id, stream_pool, m);
        stream->state = H2_STREAM_ST_OPEN;
        
        io = h2_io_set_get(m->stream_ios, stream_id);
        if (!io) {
            io = h2_io_create(stream_id, stream_pool, m->bucket_alloc);
            h2_io_set_add(m->stream_ios, io);
        }
        status = io? APR_SUCCESS : APR_ENOMEM;
        apr_thread_mutex_unlock(m->lock);
    }
    return stream;
}