static apr_status_t out_close(h2_mplx *m, h2_task *task)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (!task) {
        return APR_ECONNABORTED;
    }
    if (task->c) {
        ++task->c->keepalives;
    }
    
    stream = h2_ihash_get(m->streams, task->stream_id);
    if (!stream) {
        return APR_ECONNABORTED;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                  "h2_mplx(%s): close", task->id);
    status = h2_beam_close(task->output.beam);
    h2_beam_log(task->output.beam, m->c, APLOG_TRACE2, "out_close");
    output_consumed_signal(m, task);
    check_data_for(m, stream, 0);
    return status;
}