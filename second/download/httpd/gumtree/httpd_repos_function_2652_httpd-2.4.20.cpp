apr_status_t h2_io_out_get_brigade(h2_io *io, apr_bucket_brigade *bb, 
                                   apr_off_t len)
{
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    if (io->eos_out_read) {
        return APR_EOF;
    }
    else if (!io->bbout || APR_BRIGADE_EMPTY(io->bbout)) {
        return APR_EAGAIN;
    }
    else {
        apr_status_t status;
        apr_off_t pre_len, post_len;
        /* Allow file handles pass through without limits. If they
         * already have the lifetime of this stream, we might as well
         * pass them on to the master connection */
        apr_size_t files = INT_MAX;
        
        apr_brigade_length(bb, 0, &pre_len);
        status = h2_util_move(bb, io->bbout, len, &files, "h2_io_read_to");
        if (status == APR_SUCCESS && io->eos_out 
            && APR_BRIGADE_EMPTY(io->bbout)) {
            io->eos_out_read = 1;
        }
        apr_brigade_length(bb, 0, &post_len);
        io->output_consumed += (post_len - pre_len);
        return status;
    }
}