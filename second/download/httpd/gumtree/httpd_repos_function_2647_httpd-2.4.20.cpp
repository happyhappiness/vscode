static int add_trailer(void *ctx, const char *key, const char *value)
{
    apr_bucket_brigade *bb = ctx;
    apr_status_t status;
    
    status = apr_brigade_printf(bb, NULL, NULL, "%s: %s\r\n", 
                                key, value);
    return (status == APR_SUCCESS);
}