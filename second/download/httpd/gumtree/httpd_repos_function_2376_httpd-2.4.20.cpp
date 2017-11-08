static h2_io *open_io(h2_mplx *m, int stream_id, const h2_request *request)
{
    apr_pool_t *io_pool;
    h2_io *io;
    
    apr_pool_create(&io_pool, m->pool);
    apr_pool_tag(io_pool, "h2_io");
    io = h2_io_create(stream_id, io_pool, m->bucket_alloc, request);
    h2_io_set_add(m->stream_ios, io);
    
    return io;
}