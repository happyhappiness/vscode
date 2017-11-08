apr_status_t h2_io_in_close(h2_io *io)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (io->bbin) {
        APR_BRIGADE_INSERT_TAIL(io->bbin, 
                                apr_bucket_eos_create(io->bbin->bucket_alloc));
    }
    io->eos_in = 1;
    return APR_SUCCESS;
}