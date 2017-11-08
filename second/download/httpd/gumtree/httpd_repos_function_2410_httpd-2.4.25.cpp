static int ser_header(void *ctx, const char *name, const char *value) 
{
    apr_bucket_brigade *bb = ctx;
    apr_brigade_printf(bb, NULL, NULL, "%s: %s\r\n", name, value);
    return 1;
}