apr_status_t h2_mplx_out_rst(h2_mplx *m, int stream_id, int error)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        if (!m->aborted) {
            h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
            if (io && !io->rst_error && !io->orphaned) {
                h2_io_rst(io, error);
                if (!io->response) {
                        h2_io_set_add(m->ready_ios, io);
                }
                H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_rst");
                
                have_out_data_for(m, stream_id);
                if (io->output_drained) {
                    apr_thread_cond_signal(io->output_drained);
                }
            }
            else {
                status = APR_ECONNABORTED;
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}