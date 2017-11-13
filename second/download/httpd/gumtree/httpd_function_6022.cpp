static apr_status_t out_write(h2_mplx *m, h2_io *io, 
                              ap_filter_t* f, int blocking,
                              apr_bucket_brigade *bb,
                              struct apr_thread_cond_t *iowait)
{
    apr_status_t status = APR_SUCCESS;
    /* We check the memory footprint queued for this stream_id
     * and block if it exceeds our configured limit.
     * We will not split buckets to enforce the limit to the last
     * byte. After all, the bucket is already in memory.
     */
    while (status == APR_SUCCESS 
           && !APR_BRIGADE_EMPTY(bb) 
           && !is_aborted(m, &status)) {
        
        status = h2_io_out_write(io, bb, blocking? m->stream_max_mem : INT_MAX, 
                                 &m->tx_handles_reserved);
        io_out_consumed_signal(m, io);
        
        /* Wait for data to drain until there is room again or
         * stream timeout expires */
        h2_io_signal_init(io, H2_IO_WRITE, m->stream_timeout, iowait);
        while (status == APR_SUCCESS
               && !APR_BRIGADE_EMPTY(bb) 
               && iowait
               && (m->stream_max_mem <= h2_io_out_length(io))
               && !is_aborted(m, &status)) {
            if (!blocking) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                              "h2_mplx(%ld-%d): incomplete write", 
                              m->id, io->id);
                return APR_INCOMPLETE;
            }
            if (f) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_mplx(%ld-%d): waiting for out drain", 
                              m->id, io->id);
            }
            status = h2_io_signal_wait(m, io);
        }
        h2_io_signal_exit(io);
    }
    apr_brigade_cleanup(bb);
    
    return status;
}