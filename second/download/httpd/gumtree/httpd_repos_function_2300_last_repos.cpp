apr_status_t h2_fifo_try_peek(h2_fifo *fifo, h2_fifo_peek_fn *fn, void *ctx)
{
    return fifo_peek(fifo, fn, ctx, 0);
}