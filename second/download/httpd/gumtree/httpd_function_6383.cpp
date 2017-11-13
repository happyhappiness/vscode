apr_status_t h2_mplx_out_close(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            if (!io->response && !io->rst_error) {
                /* In case a close comes before a response was created,
                 * insert an error one so that our streams can properly
                 * reset.
                 */
                h2_response *r = h2_response_die(stream_id, APR_EGENERAL, 
                                                 io->request, m->pool);
                status = out_open(m, stream_id, r, NULL, NULL, NULL);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c,
                              "h2_mplx(%ld-%d): close, no response, no rst", 
                              m->id, io->id);
            }
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                          "h2_mplx(%ld-%d): close with eor=%s", 
                          m->id, io->id, io->eor? "yes" : "no");
            status = h2_io_out_close(io);
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_close");
            io_out_consumed_signal(m, io);
            
            have_out_data_for(m, stream_id);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}