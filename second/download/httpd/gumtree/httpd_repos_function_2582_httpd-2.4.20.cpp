static int unsubmitted_iter(void *ctx, void *val)
{
    h2_stream *stream = val;
    if (h2_stream_needs_submit(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}