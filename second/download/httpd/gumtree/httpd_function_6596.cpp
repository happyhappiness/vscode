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