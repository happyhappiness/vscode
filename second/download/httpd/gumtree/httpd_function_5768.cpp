apr_status_t h2_conn_io_write(h2_conn_io *io, 
                              const char *buf, size_t length)
{
    apr_status_t status = APR_SUCCESS;
    pass_out_ctx ctx;
    
    ctx.c = io->c;
    ctx.io = io;
    if (io->bufsize > 0) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io: buffering %ld bytes", (long)length);
                      
        if (!APR_BRIGADE_EMPTY(io->output)) {
            status = h2_conn_io_flush_int(io, 0, 0);
        }
        
        while (length > 0 && (status == APR_SUCCESS)) {
            apr_size_t avail = io->bufsize - io->buflen;
            if (avail <= 0) {
                status = h2_conn_io_flush_int(io, 0, 0);
            }
            else if (length > avail) {
                memcpy(io->buffer + io->buflen, buf, avail);
                io->buflen += avail;
                length -= avail;
                buf += avail;
            }
            else {
                memcpy(io->buffer + io->buflen, buf, length);
                io->buflen += length;
                length = 0;
                break;
            }
        }
        
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, status, io->c,
                      "h2_conn_io: writing %ld bytes to brigade", (long)length);
        status = apr_brigade_write(io->output, pass_out, &ctx, buf, length);
    }
    
    return status;
}