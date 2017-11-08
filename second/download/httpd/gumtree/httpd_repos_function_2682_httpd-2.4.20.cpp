static int input_open_iter(void *ctx, h2_stream *stream)
{
    if (h2_stream_input_is_open(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}