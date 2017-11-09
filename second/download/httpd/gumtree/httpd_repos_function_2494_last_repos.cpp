int h2_conn_io_needs_flush(h2_conn_io *io)
{
    if (!io->is_flushed) {
        apr_off_t len = h2_brigade_mem_size(io->output);
        if (len > io->flush_threshold) {
            return 1;
        }
        /* if we do not exceed flush length due to memory limits,
         * we want at least flush when we have that amount of data. */
        apr_brigade_length(io->output, 0, &len);
        return len > (4 * io->flush_threshold);
    }
    return 0;
}