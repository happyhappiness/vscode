static int head_iter(void *ctx, const char *key, const char *value) 
{
    if (!apr_strnatcasecmp("link", key)) {
        inspect_link(ctx, value, strlen(value));
    }
    return 1;
}