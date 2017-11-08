static int unsubmitted_iter(void *ctx, h2_stream *stream)
{
    if (h2_stream_needs_submit(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}