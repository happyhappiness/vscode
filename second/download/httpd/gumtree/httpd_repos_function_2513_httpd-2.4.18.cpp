apr_status_t h2_io_out_read_to(h2_io *io, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
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

    io->eos_out = *peos = h2_util_has_eos(io->bbout, *plen);
    return h2_util_move(bb, io->bbout, *plen, NULL, "h2_io_read_to");
}