
    stream = h2_ihash_get(m->streams, task->stream_id);
    if (!stream) {
        return APR_ECONNABORTED;
    }

    if (!task->response && !task->rst_error) {
        /* In case a close comes before a response was created,
         * insert an error one so that our streams can properly reset.
         */
        h2_response *r = h2_response_die(task->stream_id, 500, 
                                         task->request, m->pool);
        status = out_open(m, task->stream_id, r);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c, APLOGNO(03393)
                      "h2_mplx(%s): close, no response, no rst", task->id);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                  "h2_mplx(%s): close", task->id);
    if (task->output.beam) {
        status = h2_beam_close(task->output.beam);
        h2_beam_log(task->output.beam, task->stream_id, "out_close", m->c, 
                    APLOG_TRACE2);
    }
    output_consumed_signal(m, task);
    have_out_data_for(m, task->stream_id);
    return status;
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
        else if (!h2_ihash_empty(m->sready) || !h2_ihash_empty(m->sresume)) {
            status = APR_SUCCESS;
        }
        else {
            purge_streams(m);
            m->added_output = iowait;
            status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
