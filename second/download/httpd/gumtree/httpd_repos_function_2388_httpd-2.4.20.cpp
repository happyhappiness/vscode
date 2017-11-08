static int ngn_update_window(void *ctx, h2_io *io)
{
    ngn_update_ctx *uctx = ctx;
    if (io && io->task && io->task->assigned == uctx->ngn
        && io_out_consumed_signal(uctx->m, io)) {
        ++uctx->streams_updated;
    }
    return 1;
}