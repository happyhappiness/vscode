apr_status_t h2_conn_io_close(h2_conn_io *io, void *session)
{
    apr_bucket *b;

    /* Send out anything in our buffers */
    h2_conn_io_flush_int(io, 0);
    
    b = h2_bucket_eoc_create(io->connection->bucket_alloc, session);
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    b = apr_bucket_flush_create(io->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return ap_pass_brigade(io->connection->output_filters, io->output);
    /* and all is gone */
}