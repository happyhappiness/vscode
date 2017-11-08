apr_status_t h2_io_in_shutdown(h2_io *io)
{
    if (io->bbin) {
        apr_off_t end_len = 0;
        apr_brigade_length(io->bbin, 1, &end_len);
        io->input_consumed += end_len;
        apr_brigade_cleanup(io->bbin);
    }
    return h2_io_in_close(io);
}