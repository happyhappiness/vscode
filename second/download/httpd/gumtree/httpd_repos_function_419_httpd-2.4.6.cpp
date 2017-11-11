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
            if (name) {
                char *value = name + strlen(name) + 1;
                apr_collapse_spaces(name, name);

                if (!strcasecmp(name, a)) {
                    char *last;
                    value += strspn(value, " \t");  /* Move past leading WS */
                    last = value + strlen(value) - 1;
                    while (last >= value && apr_isspace(*last)) {
                       *last = '\0';
                       --last;
                    }

                    return ap_escape_logitem(r->pool, value);
                }
            }
            cookies = NULL;
        }
    }
    return NULL;
}