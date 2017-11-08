h2_io *h2_io_create(int id, apr_pool_t *pool, apr_bucket_alloc_t *bucket_alloc)
{
    h2_io *io = apr_pcalloc(pool, sizeof(*io));
    if (io) {
        io->id = id;
        io->pool = pool;
        io->bbin = NULL;
        io->bbout = apr_brigade_create(pool, bucket_alloc);
    }
    return io;
}