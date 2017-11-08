apr_status_t h2_io_out_close(h2_io *io)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    if (!io->eos_out_read) { /* EOS has not been read yet */
        if (!io->eos_out) {
            check_bbout(io);
            io->eos_out = 1;
            if (!h2_util_has_eos(io->bbout, -1)) {
                append_eos(io, io->bbout);
            }
        }
    }
    return APR_SUCCESS;
}