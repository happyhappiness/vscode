apr_status_t h2_io_in_write(h2_io *io, const char *d, apr_size_t len, int eos)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (io->eos_in) {
        return APR_EOF;
    }
    if (eos) {
        io->eos_in = 1;
    }
    if (len > 0) {
        check_bbin(io);
        return apr_brigade_write(io->bbin, NULL, NULL, d, len);
    }
    return APR_SUCCESS;
}