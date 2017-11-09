static void stream_input_consumed(void *ctx, h2_bucket_beam *beam, apr_off_t length)
{
    h2_stream_in_consumed(ctx, length);
}