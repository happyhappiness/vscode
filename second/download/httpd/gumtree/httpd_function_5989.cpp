static apr_status_t h2_conn_io_flush_int(h2_conn_io *io, int force)
{
    if (io->unflushed || force) {
        if (io->buflen > 0) {
            /* something in the buffer, put it in the output brigade */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
                          "h2_conn_io: flush, flushing %ld bytes", (long)io->buflen);
            bucketeer_buffer(io);
            io->buflen = 0;
        }
        
        if (force) {
            APR_BRIGADE_INSERT_TAIL(io->output,
                                    apr_bucket_flush_create(io->output->bucket_alloc));
        }
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                      "h2_conn_io: flush");
        /* Send it out */
        io->unflushed = 0;
        return pass_out(io->output, io);
        /* no more access after this, as we might have flushed an EOC bucket
         * that de-allocated us all. */
    }
    return APR_SUCCESS;
}