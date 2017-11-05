static int extract_cookie_line(ap_cookie_do * v, const char *key, const char *val)
{
    char *last1, *last2;
    char *cookie = apr_pstrdup(v->r->pool, val);
    const char *name = apr_pstrcat(v->r->pool, v->name ? v->name : "", "=", NULL);
    size_t len = strlen(name);
    const char *new_cookie = "";
    const char *comma = ",";
    char *next1;
    const char *semi = ";";
    char *next2;
    const char *sep = "";
    int cookies = 0;

    /* find the cookie called name */
    int eat = 0;
    next1 = apr_strtok(cookie, comma, &last1);
    while (next1) {
        next2 = apr_strtok(next1, semi, &last2);
        while (next2) {
            char *trim = next2;
            while (apr_isspace(*trim)) {
                trim++;
            }
            if (!strncmp(trim, name, len)) {
                if (v->encoded) {
                    if (strcmp(v->encoded, trim + len)) {
                        v->duplicated = 1;
                    }
                }
                v->encoded = apr_pstrdup(v->r->pool, trim + len);
                eat = 1;
            }
            else {
                if (*trim != '$') {
                    cookies++;
                    eat = 0;
                }
                if (!eat) {
                    new_cookie = apr_pstrcat(v->r->pool, new_cookie, sep, next2, NULL);
                }
            }
            next2 = apr_strtok(NULL, semi, &last2);
            sep = semi;
        }

        next1 = apr_strtok(NULL, comma, &last1);
        sep = comma;
    }

    /* any cookies left over? */
    if (cookies) {
        apr_table_addn(v->new_cookies, key, new_cookie);
    }

    return 1;
}