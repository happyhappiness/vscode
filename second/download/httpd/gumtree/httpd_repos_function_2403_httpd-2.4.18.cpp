static int set_header(void *ctx, const char *key, const char *value) 
{
    apr_table_setn(ctx, key, value);
    return 1;
}