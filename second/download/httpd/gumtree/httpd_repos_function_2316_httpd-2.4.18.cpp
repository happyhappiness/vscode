apr_status_t h2_mplx_in_write(h2_mplx *m, int stream_id, 
                              apr_bucket_brigade *bb)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_pre");
            status = h2_io_in_write(io, bb);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_post");
            if (io->input_arrived) {
                apr_thread_cond_signal(io->input_arrived);
            }
            io_process_events(m, io);
        }
        else {
            status = APR_EOF;
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}