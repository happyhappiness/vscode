apr_status_t h2_ififo_try_peek(h2_ififo *fifo, h2_ififo_peek_fn *fn, void *ctx)
{
    return ififo_peek(fifo, fn, ctx, 0);
}