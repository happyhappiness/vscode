h2_io *h2_io_create(int id, apr_pool_t *pool, 
                    apr_bucket_alloc_t *bucket_alloc,
                    const h2_request *request)
{
    h2_io *io = apr_pcalloc(pool, sizeof(*io));
    if (io) {
        io->id = id;
        io->pool = pool;
        io->bucket_alloc = bucket_alloc;
        io->request = h2_request_clone(pool, request);
    }
    return io;
}