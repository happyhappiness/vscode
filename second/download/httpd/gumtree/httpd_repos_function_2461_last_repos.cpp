static int ngn_update_window(void *ctx, void *val)
{
    ngn_update_ctx *uctx = ctx;
    h2_stream *stream = val;
    if (stream->task && stream->task->assigned == uctx->ngn
        && output_consumed_signal(uctx->m, stream->task)) {
        ++uctx->streams_updated;
    }
    return 1;
}