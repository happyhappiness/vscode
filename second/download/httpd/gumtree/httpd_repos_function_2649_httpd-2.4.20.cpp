apr_status_t h2_io_in_read(h2_io *io, apr_bucket_brigade *bb, 
                           apr_size_t maxlen, apr_table_t *trailers)
{
    apr_off_t start_len = 0;
    apr_status_t status;

    if (io->rst_error) {
        return APR_ECONNABORTED;
    }
    
    if (!io->bbin || APR_BRIGADE_EMPTY(io->bbin)) {
        if (io->eos_in) {
            if (!io->eos_in_written) {
                status = in_append_eos(io, bb, trailers);
                io->eos_in_written = 1;
                return status;
            }
            return APR_EOF;
        }
        return APR_EAGAIN;
    }
    
    if (io->request->chunked) {
        /* the reader expects HTTP/1.1 chunked encoding */
        check_bbtmp(io);
        status = h2_util_move(io->bbtmp, io->bbin, maxlen, NULL, "h2_io_in_read_chunk");
        if (status == APR_SUCCESS) {
            apr_off_t tmp_len = 0;
            
            apr_brigade_length(io->bbtmp, 1, &tmp_len);
            if (tmp_len > 0) {
                io->input_consumed += tmp_len;
                status = apr_brigade_printf(bb, NULL, NULL, "%lx\r\n", 
                                            (unsigned long)tmp_len);
                if (status == APR_SUCCESS) {
                    status = h2_util_move(bb, io->bbtmp, -1, NULL, "h2_io_in_read_tmp1");
                    if (status == APR_SUCCESS) {
                        status = apr_brigade_puts(bb, NULL, NULL, "\r\n");
                    }
                }
            }
            else {
                status = h2_util_move(bb, io->bbtmp, -1, NULL, "h2_io_in_read_tmp2");
            }
            apr_brigade_cleanup(io->bbtmp);
        }
    }
    else {
        apr_brigade_length(bb, 1, &start_len);
        
        status = h2_util_move(bb, io->bbin, maxlen, NULL, "h2_io_in_read");
        if (status == APR_SUCCESS) {
            apr_off_t end_len = 0;
            apr_brigade_length(bb, 1, &end_len);
            io->input_consumed += (end_len - start_len);
        }
    }
    
    if (status == APR_SUCCESS && (!io->bbin || APR_BRIGADE_EMPTY(io->bbin))) {
        if (io->eos_in) {
            if (!io->eos_in_written) {
                status = in_append_eos(io, bb, trailers);
                io->eos_in_written = 1;
            }
        }
    }
    
    if (status == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) {
        return APR_EAGAIN;
    }
    return status;
}