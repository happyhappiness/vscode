apr_status_t h2_conn_io_consider_pass(h2_conn_io *io)
{
    apr_off_t len = 0;
    
    if (!APR_BRIGADE_EMPTY(io->output)) {
        len = h2_brigade_mem_size(io->output);
    }
    len += io->buflen;
    if (len >= WRITE_BUFFER_SIZE) {
        return h2_conn_io_flush_int(io, 1, 0);
    }
    return APR_SUCCESS;
}