apr_status_t h2_io_in_read(h2_io *io, apr_bucket_brigade *bb, 
                           apr_size_t maxlen)
{
    apr_off_t start_len = 0;
    apr_bucket *last;
    apr_status_t status;

    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (!io->bbin || APR_BRIGADE_EMPTY(io->bbin)) {
        return io->eos_in? APR_EOF : APR_EAGAIN;
    }
    
    apr_brigade_length(bb, 1, &start_len);
    last = APR_BRIGADE_LAST(bb);
    status = h2_util_move(bb, io->bbin, maxlen, NULL, "h2_io_in_read");
    if (status == APR_SUCCESS) {
        apr_bucket *nlast = APR_BRIGADE_LAST(bb);
        apr_off_t end_len = 0;
        apr_brigade_length(bb, 1, &end_len);
        if (last == nlast) {
            return APR_EAGAIN;
        }
        io->input_consumed += (end_len - start_len);
    }
    return status;
}