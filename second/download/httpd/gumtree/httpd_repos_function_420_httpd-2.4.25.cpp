static const char *log_cookie(request_rec *r, char *a)
{
    const char *cookies_entry;

    /*
     * This supports Netscape version 0 cookies while being tolerant to
     * some properties of RFC2109/2965 version 1 cookies:
     * - case-insensitive match of cookie names
     * - white space between the tokens
     * It does not support the following version 1 features:
     * - quoted strings as cookie values
     * - commas to separate cookies
     */

    if ((cookies_entry = apr_table_get(r->headers_in, "Cookie"))) {
        char *cookie, *last1, *last2;
        char *cookies = apr_pstrdup(r->pool, cookies_entry);

        while ((cookie = apr_strtok(cookies, ";", &last1))) {
            char *name = apr_strtok(cookie, "=", &last2);
            /* last2 points to the next char following an '=' delim,
               or the trailing NUL char of the string */
            char *value = last2;
            if (name && *name &&  value && *value) {
                char *last = value - 2;
                /* Move past leading WS */
                name += strspn(name, " \t");
                while (last >= name && apr_isspace(*last)) {
                    *last = '\0';
                    --last;
                }

                if (!strcasecmp(name, a)) {
                    /* last1 points to the next char following the ';' delim,
                       or the trailing NUL char of the string */
                    last = last1 - (*last1 ? 2 : 1);
                    /* Move past leading WS */
                    value += strspn(value, " \t");
                    while (last >= value && apr_isspace(*last)) {
                       *last = '\0';
                       --last;
                    }

                    return ap_escape_logitem(r->pool, value);
                }
            }
            /* Iterate the remaining tokens using apr_strtok(NULL, ...) */
            cookies = NULL;
        }
    }
    return NULL;
}