apr_status_t h2_mplx_in_close(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            status = h2_io_in_close(io);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_close");
            h2_io_signal(io, H2_IO_READ);
            io_in_consumed_signal(m, io);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}