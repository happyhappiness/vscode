static apr_status_t widen_envvar_name (apr_wchar_t *buffer,
                                       apr_size_t bufflen,
                                       const char *envvar)
{
    apr_size_t inchars;
    apr_status_t status;

    inchars = strlen(envvar) + 1;
    status = apr_conv_utf8_to_ucs2(envvar, &inchars, buffer, &bufflen);
    if (status == APR_INCOMPLETE)
        status = APR_ENAMETOOLONG;

    return status;
}