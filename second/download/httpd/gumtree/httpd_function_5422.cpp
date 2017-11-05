static apr_status_t bucketeer_buffer(h2_conn_io *io) {
    const char *data = io->buffer;
    apr_size_t remaining = io->buflen;
    apr_bucket *b;
    int bcount, i;

    if (io->write_size > WRITE_SIZE_INITIAL 
        && (io->cooldown_usecs > 0)
        && (apr_time_now() - io->last_write) >= io->cooldown_usecs) {
        /* long time not written, reset write size */
        io->write_size = WRITE_SIZE_INITIAL;
        io->bytes_written = 0;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                      "h2_conn_io(%ld): timeout write size reset to %ld", 
                      (long)io->connection->id, (long)io->write_size);
    }
    else if (io->write_size < WRITE_SIZE_MAX 
             && io->bytes_written >= io->warmup_size) {
        /* connection is hot, use max size */
        io->write_size = WRITE_SIZE_MAX;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                      "h2_conn_io(%ld): threshold reached, write size now %ld", 
                      (long)io->connection->id, (long)io->write_size);
    }
    
    bcount = (int)(remaining / io->write_size);
    for (i = 0; i < bcount; ++i) {
        b = apr_bucket_transient_create(data, io->write_size, 
                                        io->output->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
        data += io->write_size;
        remaining -= io->write_size;
    }
    
    if (remaining > 0) {
        b = apr_bucket_transient_create(data, remaining, 
                                        io->output->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
    }
    return APR_SUCCESS;
}