
    stream = h2_ihash_get(m->streams, task->stream_id);
    if (!stream) {
        return APR_ECONNABORTED;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                  "h2_mplx(%s): close", task->id);
    status = h2_beam_close(task->output.beam);
    h2_beam_log(task->output.beam, task->stream_id, "out_close", m->c, 
                APLOG_TRACE2);
    output_consumed_signal(m, task);
    have_out_data_for(m, stream, 0);
    return status;
}

apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else if (!h2_iq_empty(m->readyq)) {
            status = APR_SUCCESS;
        }
        else {
            purge_streams(m);
            m->added_output = iowait;
            status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
