static int update_window(void *ctx, h2_io *io)
{
    update_ctx *uctx = (update_ctx*)ctx;
    if (io_in_consumed_signal(uctx->m, io)) {
        ++uctx->streams_updated;
    }
    return 1;
}