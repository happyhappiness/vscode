            apr_thread_mutex_unlock(m->lock);
        }
    }
    return status;
}

apr_status_t h2_mplx_out_close(h2_mplx *m, int stream_id, apr_table_t *trailers)
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
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c,
                              "h2_mplx(%ld-%d): close with trailers=%s", 
                              m->id, io->id, trailers? "yes" : "no");
                status = h2_io_out_close(io, trailers);
                H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_close");
                
                have_out_data_for(m, stream_id);
                if (m->aborted) {
                    /* if we were the last output, the whole session might
                     * have gone down in the meantime.
                     */
                    return APR_SUCCESS;
