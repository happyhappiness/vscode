static void check_bbin(h2_io *io)
{
    if (!io->bbin) {
        io->bbin = apr_brigade_create(io->pool, io->bucket_alloc);
    }
}