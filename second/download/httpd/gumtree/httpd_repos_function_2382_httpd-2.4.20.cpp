static int latest_repeatable_busy_unsubmitted_iter(void *data, h2_io *io)
{
    io_iter_ctx *ctx = data;
    if (io->worker_started && !io->worker_done
        && h2_io_is_repeatable(io)
        && !h2_io_set_get(ctx->m->redo_ios, io->id)) {
        /* this io occupies a worker, the response has not been submitted yet,
         * not been cancelled and it is a repeatable request
         * -> it can be re-scheduled later */
        if (!ctx->io || ctx->io->started_at < io->started_at) {
            /* we did not have one or this one was started later */
            ctx->io = io;
        }
    }
    return 1;
}