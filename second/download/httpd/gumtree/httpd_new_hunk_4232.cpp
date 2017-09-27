        m->aborted = 1;
        h2_ngn_shed_abort(m->ngn_shed);
        leave_mutex(m, acquired);
    }
}

apr_status_t h2_mplx_stream_done(h2_mplx *m, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
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

void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
{
    m->input_consumed = cb;
    m->input_consumed_ctx = ctx;
}

static apr_status_t out_open(h2_mplx *m, int stream_id, h2_response *response)
{
    apr_status_t status = APR_SUCCESS;
    h2_task *task = h2_ihash_get(m->tasks, stream_id);
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    
    if (!task || !stream) {
        return APR_ECONNABORTED;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%s): open response: %d, rst=%d",
                  task->id, response->http_status, response->rst_error);
    
    h2_task_set_response(task, response);
    
    if (task->output.beam) {
        h2_beam_buffer_size_set(task->output.beam, m->stream_max_mem);
        h2_beam_timeout_set(task->output.beam, m->stream_timeout);
        h2_beam_on_consumed(task->output.beam, stream_output_consumed, task);
        m->tx_handles_reserved -= h2_beam_get_files_beamed(task->output.beam);
        h2_beam_on_file_beam(task->output.beam, can_beam_file, m);
        h2_beam_mutex_set(task->output.beam, beam_enter, task->cond, m);
    }
    
    h2_ihash_add(m->sready, stream);
    if (response && response->http_status < 300) {
        /* we might see some file buckets in the output, see
         * if we have enough handles reserved. */
        check_tx_reservation(m);
    }
    have_out_data_for(m, stream_id);
    return status;
}

apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_response *response)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            status = out_open(m, stream_id, response);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

static apr_status_t out_close(h2_mplx *m, h2_task *task)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (!task) {
        return APR_ECONNABORTED;
    }

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
            if (APLOGctrace2(m->c)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%ld): trywait on data for %f ms)",
                              m->id, timeout/1000.0);
