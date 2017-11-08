static int suspended_iter(void *ctx, h2_stream *stream)
{
    if (h2_stream_is_suspended(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}