
apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_response *response,
                              ap_filter_t* f, apr_bucket_brigade *bb,
                              struct apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            status = out_open(m, stream_id, response, f, bb, iowait);
            if (APLOGctrace1(m->c)) {
                h2_util_bb_log(m->c, stream_id, APLOG_TRACE1, "h2_mplx_out_open", bb);
            }
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_out_write(h2_mplx *m, int stream_id, 
                               ap_filter_t* f, int blocking,
                               apr_bucket_brigade *bb,
                               struct apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            status = out_write(m, io, f, blocking, bb, iowait);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                          "h2_mplx(%ld-%d): write", m->id, io->id);
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_write");
            
            have_out_data_for(m, stream_id);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

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

int h2_mplx_out_has_data_for(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int has_data = 0;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            has_data = h2_io_out_has_data(io);
        }
        else {
            has_data = 0;
        }
        leave_mutex(m, acquired);
    }
    return has_data;
}

apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            m->added_output = iowait;
            status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
            if (APLOGctrace2(m->c)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%ld): trywait on data for %f ms)",
                              m->id, timeout/1000.0);
            }
            m->added_output = NULL;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

static void have_out_data_for(h2_mplx *m, int stream_id)
{
