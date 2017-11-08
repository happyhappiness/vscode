apr_status_t h2_mplx_out_read_to(h2_mplx *m, int stream_id, 
                                 apr_bucket_brigade *bb, 
                                 apr_off_t *plen, int *peos,
                                 apr_table_t **ptrailers)
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
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_read_to_pre");
            
            status = h2_io_out_read_to(io, bb, plen, peos);
            
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_read_to_post");
            if (status == APR_SUCCESS && io->output_drained) {
                apr_thread_cond_signal(io->output_drained);
            }
        }
        else {
            status = APR_ECONNABORTED;
        }
        *ptrailers = (*peos && io->response)? io->response->trailers : NULL;
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}