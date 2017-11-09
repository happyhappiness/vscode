static apr_status_t out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    
    if (!stream || !stream->task || m->aborted) {
        return APR_ECONNABORTED;
    }
    
    ap_assert(stream->output == NULL);
    stream->output = beam;
    
    if (APLOGctrace2(m->c)) {
        h2_beam_log(beam, m->c, APLOG_TRACE2, "out_open");
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                      "h2_mplx(%s): out open", stream->task->id);
    }
    
    h2_beam_on_consumed(stream->output, NULL, stream_output_consumed, stream);
    h2_beam_on_produced(stream->output, output_produced, stream);
    if (stream->task->output.copy_files) {
        h2_beam_on_file_beam(stream->output, h2_beam_no_files, NULL);
    }
    
    /* time to protect the beam against multi-threaded use */
    h2_beam_mutex_enable(stream->output);
    
    /* we might see some file buckets in the output, see
     * if we have enough handles reserved. */
    check_data_for(m, stream, 0);
    return status;
}