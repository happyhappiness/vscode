}

apr_status_t h2_conn_io_write(h2_conn_io *io, 
                              const char *buf, size_t length)
{
    apr_status_t status = APR_SUCCESS;
    io->unflushed = 1;
    
    if (io->buffer_output) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
                      "h2_conn_io: buffering %ld bytes", (long)length);
        while (length > 0 && (status == APR_SUCCESS)) {
            apr_size_t avail = io->bufsize - io->buflen;
            if (avail <= 0) {
                bucketeer_buffer(io);
                status = flush_out(io->output, io);
                io->buflen = 0;
            }
            else if (length > avail) {
                memcpy(io->buffer + io->buflen, buf, avail);
                io->buflen += avail;
                length -= avail;
