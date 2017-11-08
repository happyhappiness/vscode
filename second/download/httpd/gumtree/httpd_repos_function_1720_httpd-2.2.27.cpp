static void *create_includes_dir_config(apr_pool_t *p, char *dummy)
{
    include_dir_config *result = apr_palloc(p, sizeof(include_dir_config));

    result->default_error_msg = DEFAULT_ERROR_MSG;
    result->default_time_fmt  = DEFAULT_TIME_FORMAT;
    result->undefined_echo    = DEFAULT_UNDEFINED_ECHO;
    result->xbithack          = DEFAULT_XBITHACK;
    result->accessenable      = DEFAULT_ACCESSENABLE;
    result->lastmodified      = DEFAULT_LASTMODIFIED;
    result->etag              = DEFAULT_ETAG;

    return result;
}