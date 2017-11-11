static apr_status_t ap_default_log_writer( request_rec *r,
                           void *handle,
                           const char **strs,
                           int *strl,
                           int nelts,
                           apr_size_t len)

{
    char *str;
    char *s;
    int i;
    apr_status_t rv;

    str = apr_palloc(r->pool, len + 1);

    for (i = 0, s = str; i < nelts; ++i) {
        memcpy(s, strs[i], strl[i]);
        s += strl[i];
    }

    rv = apr_file_write((apr_file_t*)handle, str, &len);

    return rv;
}