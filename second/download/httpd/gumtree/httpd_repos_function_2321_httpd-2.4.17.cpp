static apr_status_t flush_out(apr_bucket_brigade *bb, void *ctx) 
{
    h2_conn_io *io = (h2_conn_io*)ctx;
    apr_status_t status;
    apr_off_t bblen;
    
    ap_update_child_status(io->connection->sbh, SERVER_BUSY_WRITE, NULL);
    status = apr_brigade_length(bb, 1, &bblen);
    if (status == APR_SUCCESS) {
        status = ap_pass_brigade(io->connection->output_filters, bb);
        if (status == APR_SUCCESS) {
            io->bytes_written += (apr_size_t)bblen;
            io->last_write = apr_time_now();
        }
        apr_brigade_cleanup(bb);
    }
    return status;
}