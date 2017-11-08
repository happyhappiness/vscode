apr_status_t h2_mplx_out_get_brigade(h2_mplx *m, int stream_id, 
                                     apr_bucket_brigade *bb, 
                                     apr_off_t len, apr_table_t **ptrailers)
{
    apr_status_t status;
    int acquired;

    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_pre");
            
            status = h2_io_out_get_brigade(io, bb, len);
            
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_post");
            if (status == APR_SUCCESS) {
                h2_io_signal(io, H2_IO_WRITE);
            }
        }
        else {
            status = APR_ECONNABORTED;
        }
        *ptrailers = io->response? io->response->trailers : NULL;
        leave_mutex(m, acquired);
    }
    return status;
}