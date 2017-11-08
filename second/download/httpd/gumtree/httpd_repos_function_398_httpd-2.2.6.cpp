static const char *log_cookie(request_rec *r, char *a)
{
    const char *cookies;
    const char *start_cookie;

    if ((cookies = apr_table_get(r->headers_in, "Cookie"))) {
        if ((start_cookie = ap_strstr_c(cookies,a))) {
            char *cookie, *end_cookie;
            start_cookie += strlen(a) + 1; /* cookie_name + '=' */
            cookie = apr_pstrdup(r->pool, start_cookie);
            /* kill everything in cookie after ';' */
            end_cookie = strchr(cookie, ';');
            if (end_cookie) {
                *end_cookie = '\0';
            }
            return ap_escape_logitem(r->pool, cookie);
        }
    }
    return NULL;
}