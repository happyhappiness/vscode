static apr_status_t bbout(apr_bucket_brigade *bb, const char *fmt, ...)
{
    va_list args;
    apr_status_t rv;

    va_start(args, fmt);
    rv = apr_brigade_vprintf(bb, NULL, NULL, fmt, args);
    va_end(args);

    return rv;
}