apr_status_t h2_conn_io_read(h2_conn_io *io,
                             apr_read_type_e block,
                             h2_conn_io_on_read_cb on_read_cb,
                             void *puser)
{
    apr_status_t status;
    int done = 0;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                  "h2_conn_io: try read, block=%d", block);
    
    if (!APR_BRIGADE_EMPTY(io->input)) {
        /* Seems something is left from a previous read, lets
         * satisfy our caller with the data we already have. */
        status = h2_conn_io_bucket_read(io, block, on_read_cb, puser, &done);
        apr_brigade_cleanup(io->input);
        if (status != APR_SUCCESS || done) {
            return status;
        }
    }

    /* We only do a blocking read when we have no streams to process. So,
     * in httpd scoreboard lingo, we are in a KEEPALIVE connection state.
     * When reading non-blocking, we do have streams to process and update
     * child with NULL request. That way, any current request information
     * in the scoreboard is preserved.
     */
    if (block == APR_BLOCK_READ) {
        ap_update_child_status_from_conn(io->connection->sbh, 
                                         SERVER_BUSY_KEEPALIVE, 
                                         io->connection);
    }
    else {
        ap_update_child_status(io->connection->sbh, SERVER_BUSY_READ, NULL);
    }

    /* TODO: replace this with a connection filter itself, so that we
     * no longer need to transfer incoming buckets to our own brigade. 
     */
    status = ap_get_brigade(io->connection->input_filters,
                            io->input, AP_MODE_READBYTES,
                            block, 64 * 4096);
    switch (status) {
        case APR_SUCCESS:
            return h2_conn_io_bucket_read(io, block, on_read_cb, puser, &done);
        case APR_EOF:
        case APR_EAGAIN:
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, io->connection,
                          "h2_conn_io: error reading");
            break;
    }
    return status;
}