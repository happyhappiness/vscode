static int copy_header(void *ctx, const char *name, const char *value)
{
    apr_table_t *headers = ctx;
    
    apr_table_addn(headers, name, value);
    return 1;
}