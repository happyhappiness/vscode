static h2_io *open_io(h2_mplx *m, int stream_id)
{
    apr_pool_t *io_pool = m->spare_pool;
    h2_io *io;
    
    if (!io_pool) {
        apr_pool_create(&io_pool, m->pool);
    }
    else {
        m->spare_pool = NULL;
    }
    
    io = h2_io_create(stream_id, io_pool, m->bucket_alloc);
    h2_io_set_add(m->stream_ios, io);
    
    return io;
}