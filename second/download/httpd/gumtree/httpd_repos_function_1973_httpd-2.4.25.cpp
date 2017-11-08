static const char *hc_get_body(request_rec *r)
{
    apr_off_t length;
    apr_size_t len;
    apr_status_t rv;
    char *buf;

    if (!r || !r->kept_body)
        return "";

    rv = apr_brigade_length(r->kept_body, 1, &length);
    len = (apr_size_t)length;
    if (rv != APR_SUCCESS || len == 0)
        return "";

    buf = apr_palloc(r->pool, len + 1);
    rv = apr_brigade_flatten(r->kept_body, buf, &len);
    if (rv != APR_SUCCESS)
        return "";
    buf[len] = '\0'; /* ensure */
    return (const char*)buf;
}