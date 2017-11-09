static int stream_destroy_iter(void *ctx, void *val) 
{   
    h2_mplx *m = ctx;
    h2_stream *stream = val;

    h2_ihash_remove(m->spurge, stream->id);
    ap_assert(stream->state == H2_SS_CLEANUP);
    
    if (stream->input) {
        /* Process outstanding events before destruction */
        input_consumed_signal(m, stream);    
        h2_beam_log(stream->input, m->c, APLOG_TRACE2, "stream_destroy");
        h2_beam_destroy(stream->input);
        stream->input = NULL;
    }

    if (stream->task) {
        task_destroy(m, stream->task);
        stream->task = NULL;
    }
    h2_stream_destroy(stream);
    return 0;
}