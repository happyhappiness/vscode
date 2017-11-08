void h2_io_destroy(h2_io *io)
{
    if (io->pool) {
        apr_pool_destroy(io->pool);
        /* gone */
    }
}