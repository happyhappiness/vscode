static char *http2env(apr_pool_t *a, const char *w)
{
    char *res = (char *)apr_palloc(a, sizeof("HTTP_") + strlen(w));
    char *cp = res;
    char c;

    *cp++ = 'H';
    *cp++ = 'T';
    *cp++ = 'T';
    *cp++ = 'P';
    *cp++ = '_';

    while ((c = *w++) != 0) {
        if (!apr_isalnum(c)) {
            *cp++ = '_';
        }
        else {
            *cp++ = apr_toupper(c);
        }
    }
    *cp = 0;

    return res;
}