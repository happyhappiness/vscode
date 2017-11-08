static void check_bbout(h2_io *io)
{
    if (!io->bbout) {
        io->bbout = apr_brigade_create(io->pool, io->bucket_alloc);
    }
}