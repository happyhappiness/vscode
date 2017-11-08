static void *cfg_getstr(void *buf, size_t bufsiz, void *param)
{
    apr_file_t *cfp = (apr_file_t *) param;
    apr_status_t rv;
    rv = apr_file_gets(buf, bufsiz, cfp);
    if (rv == APR_SUCCESS || (APR_STATUS_IS_EOF(rv) && strcmp(buf, "")))
        return buf;
    return NULL;
}