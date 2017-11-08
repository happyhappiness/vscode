apr_status_t h2_io_out_readx(h2_io *io,  
                             h2_io_data_cb *cb, void *ctx, 
                             apr_size_t *plen, int *peos)
{
    if (cb == NULL) {
        /* just checking length available */
        return h2_util_bb_avail(io->bbout, plen, peos);
    }
    return h2_util_bb_readx(io->bbout, cb, ctx, plen, peos);
}