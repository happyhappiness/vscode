static char *escape_uri(apr_pool_t *p, const char *path) {
    char *copy = apr_palloc(p, 3 * strlen(path) + 3);
    const unsigned char *s = (const unsigned char *)path;
    unsigned char *d = (unsigned char *)copy;
    unsigned c;

    while ((c = *s)) {
        if (apr_isalnum(c) || c == '_') {
            *d++ = c;
        }
        else if (c == ' ') {
            *d++ = '+';
        }
        else {
            d = c2x(c, '%', d);
        }
        ++s;
    }
    *d = '\0';
    return copy;
}