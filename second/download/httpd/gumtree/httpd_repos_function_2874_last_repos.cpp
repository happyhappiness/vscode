h2_alt_svc *h2_alt_svc_parse(const char *s, apr_pool_t *pool)
{
    const char *sep = ap_strchr_c(s, '=');
    if (sep) {
        const char *alpn = apr_pstrmemdup(pool, s, sep - s);
        const char *host = NULL;
        int port = 0;
        s = sep + 1;
        sep = ap_strchr_c(s, ':');  /* mandatory : */
        if (sep) {
            if (sep != s) {    /* optional host */
                host = apr_pstrmemdup(pool, s, sep - s);
            }
            s = sep + 1;
            if (*s) {          /* must be a port number */
                port = (int)apr_atoi64(s);
                if (port > 0 && port < (0x1 << 16)) {
                    h2_alt_svc *as = apr_pcalloc(pool, sizeof(*as));
                    as->alpn = alpn;
                    as->host = host;
                    as->port = port;
                    return as;
                }
            }
        }
    }
    return NULL;
}