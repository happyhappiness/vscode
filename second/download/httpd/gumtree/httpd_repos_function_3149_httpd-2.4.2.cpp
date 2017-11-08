static char *http2env(request_rec *r, const char *w)
{
    char *res = (char *)apr_palloc(r->pool, sizeof("HTTP_") + strlen(w));
    char *cp = res;
    char c;

    *cp++ = 'H';
    *cp++ = 'T';
    *cp++ = 'T';
    *cp++ = 'P';
    *cp++ = '_';

    while ((c = *w++) != 0) {
        if (apr_isalnum(c)) {
            *cp++ = apr_toupper(c);
        }
        else if (c == '-') {
            *cp++ = '_';
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                          "Not exporting header with invalid name as envvar: %s",
                          ap_escape_logitem(r->pool, w));
            return NULL;
        }
    }
    *cp = 0;

    return res;
}