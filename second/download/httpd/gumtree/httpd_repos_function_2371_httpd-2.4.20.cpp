apr_status_t h2_mplx_out_rst(h2_mplx *m, int stream_id, int error)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->rst_error && !io->orphaned) {
            h2_io_rst(io, error);
            if (!io->response) {
                h2_io_set_add(m->ready_ios, io);
            }
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_rst");
            
            have_out_data_for(m, stream_id);
            h2_io_signal(io, H2_IO_WRITE);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}