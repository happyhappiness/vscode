static void *create_includes_dir_config(apr_pool_t *p, char *dummy)
{
    include_dir_config *result =
        (include_dir_config *)apr_palloc(p, sizeof(include_dir_config));
    enum xbithack *xbh = (enum xbithack *) apr_palloc(p, sizeof(enum xbithack));
    *xbh = DEFAULT_XBITHACK;
    result->default_error_msg = DEFAULT_ERROR_MSG;
    result->default_time_fmt = DEFAULT_TIME_FORMAT;
    result->xbithack = xbh;
    return result;
}