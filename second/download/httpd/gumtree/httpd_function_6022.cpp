apr_status_t h2_mplx_in_read(h2_mplx *m, apr_read_type_e block,
                             int stream_id, apr_bucket_brigade *bb, 
                             apr_table_t *trailers,
                             struct apr_thread_cond_t *iowait)
{
    apr_status_t status; 
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_pre");
            
            h2_io_signal_init(io, H2_IO_READ, m->stream_timeout, iowait);
            status = h2_io_in_read(io, bb, -1, trailers);
            while (APR_STATUS_IS_EAGAIN(status) 
                   && !is_aborted(m, &status)
                   && block == APR_BLOCK_READ) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                              "h2_mplx(%ld-%d): wait on in data (BLOCK_READ)", 
                              m->id, stream_id);
                status = h2_io_signal_wait(m, io);
                if (status == APR_SUCCESS) {
                    status = h2_io_in_read(io, bb, -1, trailers);
                }
            }
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_post");
            h2_io_signal_exit(io);
        }
        else {
            status = APR_EOF;
        }
        leave_mutex(m, acquired);
    }
    return status;
}