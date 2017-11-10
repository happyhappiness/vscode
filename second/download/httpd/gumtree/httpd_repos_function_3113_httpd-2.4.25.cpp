static void *create_includes_dir_config(apr_pool_t *p, char *dummy)
{
    include_dir_config *result = apr_pcalloc(p, sizeof(include_dir_config));

    result->xbithack          = XBITHACK_UNSET;
    result->lastmodified      = UNSET;
    result->etag              = UNSET;
    result->legacy_expr       = UNSET;

    return result;
}