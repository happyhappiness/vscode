apr_status_t h2_io_out_readx(h2_io *io,  
                             h2_io_data_cb *cb, void *ctx, 
                             apr_off_t *plen, int *peos)
{
    apr_status_t status;
    
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (io->eos_out) {
        *plen = 0;
        *peos = 1;
        return APR_SUCCESS;
    }
    else if (!io->bbout) {
        *plen = 0;
        *peos = 0;
        return APR_EAGAIN;
    }
    
    if (cb == NULL) {
        /* just checking length available */
        status = h2_util_bb_avail(io->bbout, plen, peos);
    }
    else {
        status = h2_util_bb_readx(io->bbout, cb, ctx, plen, peos);
        if (status == APR_SUCCESS) {
            io->eos_out = *peos;
        }
    }
    
    return status;
}