apr_status_t h2_io_in_close(h2_io *io)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    io->eos_in = 1;
    return APR_SUCCESS;
}