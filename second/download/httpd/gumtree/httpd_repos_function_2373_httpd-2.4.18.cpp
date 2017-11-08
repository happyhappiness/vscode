apr_status_t h2_conn_io_consider_flush(h2_conn_io *io)
{
    apr_status_t status = APR_SUCCESS;
    
    /* The HTTP/1.1 network output buffer/flush behaviour does not
     * give optimal performance in the HTTP/2 case, as the pattern of
     * buckets (data/eor/eos) is different.
     * As long as we have not found out the "best" way to deal with
     * this, force a flush at least every WRITE_BUFFER_SIZE amount
     * of data.
     */
    if (io->unflushed) {
        apr_off_t len = 0;
        if (!APR_BRIGADE_EMPTY(io->output)) {
            apr_brigade_length(io->output, 0, &len);
        }
        len += io->buflen;
        if (len >= WRITE_BUFFER_SIZE) {
            return h2_conn_io_pass(io);
        }
    }
    return status;
}