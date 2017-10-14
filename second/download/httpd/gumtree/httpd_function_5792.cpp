apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    if (io->unflushed) {
        apr_status_t status; 
        if (io->buflen > 0) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
                          "h2_conn_io: flush, flushing %ld bytes", (long)io->buflen);
            bucketeer_buffer(io);
            io->buflen = 0;
        }
        /* Append flush.
         */
        APR_BRIGADE_INSERT_TAIL(io->output,
                                apr_bucket_flush_create(io->output->bucket_alloc));
        
        /* Send it out through installed filters (TLS) to the client */
        status = flush_out(io->output, io);
        
        if (status == APR_SUCCESS) {
            /* These are all fine and no reason for concern. Everything else
             * is interesting. */
            io->unflushed = 0;
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, io->connection,
                          "h2_conn_io: flush error");
        }
        
        return status;
    }
    return APR_SUCCESS;
}