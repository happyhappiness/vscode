static int stream_iter_wrap(void *ctx, void *stream)
{
    stream_iter_ctx_t *x = ctx;
    return x->cb(stream, x->ctx);
}