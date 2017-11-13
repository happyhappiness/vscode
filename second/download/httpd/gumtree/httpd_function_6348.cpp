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