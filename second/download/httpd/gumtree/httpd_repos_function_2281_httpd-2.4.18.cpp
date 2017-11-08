static apr_status_t input_flush(apr_bucket_brigade *bb, void *ctx) 
{
    (void)bb;
    return h2_stream_input_flush(ctx);
}