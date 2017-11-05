apr_status_t h2_mplx_stream_done(h2_mplx *m, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                      "h2_mplx(%ld-%d): marking stream as done.", 
                      m->id, stream->id);
        stream_done(m, stream, stream->rst_error);
        purge_streams(m);
        leave_mutex(m, acquired);
    }
    return status;
}