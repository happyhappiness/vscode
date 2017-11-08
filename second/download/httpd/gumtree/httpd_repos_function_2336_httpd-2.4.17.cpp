static apr_status_t flush(apr_bucket_brigade *bb, void *ctx) 
{
    (void)bb;
    return h2_to_h1_flush((h2_to_h1*)ctx);
}