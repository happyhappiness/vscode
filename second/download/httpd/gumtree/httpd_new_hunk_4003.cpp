                                        io->output->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
    }
    return APR_SUCCESS;
}

apr_status_t h2_conn_io_writeb(h2_conn_io *io, apr_bucket *b)
{
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return APR_SUCCESS;
}

static apr_status_t h2_conn_io_flush_int(h2_conn_io *io, int flush, int eoc)
{
    pass_out_ctx ctx;
    apr_bucket *b;
    
    if (io->buflen == 0 && APR_BRIGADE_EMPTY(io->output)) {
        return APR_SUCCESS;
    }
        
    if (io->buflen > 0) {
        /* something in the buffer, put it in the output brigade */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io: flush, flushing %ld bytes", 
                      (long)io->buflen);
        bucketeer_buffer(io);
    }
    
    if (flush) {
        b = apr_bucket_flush_create(io->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c, "h2_conn_io: flush");
    io->buflen = 0;
    ctx.c = io->c;
    ctx.io = eoc? NULL : io;
    
    return pass_out(io->output, &ctx);
    /* no more access after this, as we might have flushed an EOC bucket
     * that de-allocated us all. */
}

apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    return h2_conn_io_flush_int(io, 1, 0);
}

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

apr_status_t h2_conn_io_write_eoc(h2_conn_io *io, h2_session *session)
{
    apr_bucket *b = h2_bucket_eoc_create(io->c->bucket_alloc, session);
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return h2_conn_io_flush_int(io, 0, 1);
}

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
