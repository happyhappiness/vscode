static void check_bbtmp(h2_io *io)
{
    if (!io->bbtmp) {
        io->bbtmp = apr_brigade_create(io->pool, io->bucket_alloc);
    }
}