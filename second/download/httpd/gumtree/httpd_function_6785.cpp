static apr_status_t out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status = APR_SUCCESS;
    h2_task *task = h2_ihash_get(m->tasks, stream_id);
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    apr_size_t beamed_count;
    
    if (!task || !stream) {
        return APR_ECONNABORTED;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                  "h2_mplx(%s): out open", task->id);
                      
    h2_beam_on_consumed(stream->output, stream_output_consumed, task);
    h2_beam_on_produced(stream->output, output_produced, m);
    beamed_count = h2_beam_get_files_beamed(stream->output);
    if (m->tx_handles_reserved >= beamed_count) {
        m->tx_handles_reserved -= beamed_count;
    }
    else {
        m->tx_handles_reserved = 0;
    }
    if (!task->output.copy_files) {
        h2_beam_on_file_beam(stream->output, can_beam_file, m);
    }
    
    /* time to protect the beam against multi-threaded use */
    h2_beam_mutex_set(stream->output, beam_enter, task->cond, m);
    
    /* we might see some file buckets in the output, see
     * if we have enough handles reserved. */
    check_tx_reservation(m);
    have_out_data_for(m, stream, 0);
    return status;
}