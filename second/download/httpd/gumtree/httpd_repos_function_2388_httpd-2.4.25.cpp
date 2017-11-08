static int ngn_update_window(void *ctx, void *val)
{
    ngn_update_ctx *uctx = ctx;
    h2_task *task = val;
    if (task && task->assigned == uctx->ngn
        && output_consumed_signal(uctx->m, task)) {
        ++uctx->streams_updated;
    }
    return 1;
}