static void *cfg_getstr(void *buf, size_t bufsiz, void *param)
{
    apr_file_t *cfp = (apr_file_t *) param;
    apr_status_t rv;
    rv = apr_file_gets(buf, bufsiz, cfp);
    if (rv == APR_SUCCESS) {
        return buf;
    }
    return NULL;
}