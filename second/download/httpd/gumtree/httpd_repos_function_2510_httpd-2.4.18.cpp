apr_status_t h2_io_in_write(h2_io *io, apr_bucket_brigade *bb)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (io->eos_in) {
        return APR_EOF;
    }
    io->eos_in = h2_util_has_eos(bb, -1);
    if (!APR_BRIGADE_EMPTY(bb)) {
        if (!io->bbin) {
            io->bbin = apr_brigade_create(io->pool, io->bucket_alloc);
        }
        return h2_util_move(io->bbin, bb, -1, NULL, "h2_io_in_write");
    }
    return APR_SUCCESS;
}