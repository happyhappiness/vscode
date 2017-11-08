static int timed_out_busy_iter(void *data, h2_io *io)
{
    io_iter_ctx *ctx = data;
    if (io->worker_started && !io->worker_done
        && (ctx->now - io->started_at) > ctx->m->stream_timeout) {
        /* timed out stream occupying a worker, found */
        ctx->io = io;
        return 0;
    }
    return 1;
}