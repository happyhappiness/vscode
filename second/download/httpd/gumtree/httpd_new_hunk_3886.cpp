    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        status = out_open(m, stream_id, response, f, bb, iowait);
        if (APLOGctrace1(m->c)) {
            h2_util_bb_log(m->c, stream_id, APLOG_TRACE1, "h2_mplx_out_open", bb);
        }
        if (m->aborted) {
            return APR_ECONNABORTED;
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}


apr_status_t h2_mplx_out_write(h2_mplx *m, int stream_id, 
                               ap_filter_t* f, apr_bucket_brigade *bb,
                               apr_table_t *trailers,
                               struct apr_thread_cond_t *iowait)
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
                status = out_write(m, io, f, bb, trailers, iowait);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c,
                              "h2_mplx(%ld-%d): write with trailers=%s", 
                              m->id, io->id, trailers? "yes" : "no");
                H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_write");
                
                have_out_data_for(m, stream_id);
                if (m->aborted) {
                    return APR_ECONNABORTED;
                }
            }
            else {
