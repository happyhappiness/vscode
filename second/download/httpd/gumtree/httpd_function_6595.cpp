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