static char *escape_absolute_uri(apr_pool_t *p, char *uri, unsigned scheme)
{
    char *cp;

    /* be safe.
     * NULL should indicate elsewhere, that something's wrong
     */
    if (!scheme || strlen(uri) < scheme) {
        return NULL;
    }

    cp = uri + scheme;

    /* scheme with authority part? */
    if (cp[-1] == '/') {
        /* skip host part */
        while (*cp && *cp != '/') {
            ++cp;
        }

        /* nothing after the hostpart. ready! */
        if (!*cp || !*++cp) {
            return apr_pstrdup(p, uri);
        }

        /* remember the hostname stuff */
        scheme = cp - uri;

        /* special thing for ldap.
         * The parts are separated by question marks. From RFC 2255:
         *     ldapurl = scheme "://" [hostport] ["/"
         *               [dn ["?" [attributes] ["?" [scope]
         *               ["?" [filter] ["?" extensions]]]]]]
         */
        if (!strncasecmp(uri, "ldap", 4)) {
            char *token[5];
            int c = 0;

            token[0] = cp = apr_pstrdup(p, cp);
            while (*cp && c < 4) {
                if (*cp == '?') {
                    token[++c] = cp + 1;
                    *cp = '\0';
                }
                ++cp;
            }

            return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
                                          ap_escape_uri(p, token[0]),
                               (c >= 1) ? "?" : NULL,
                               (c >= 1) ? ap_escape_uri(p, token[1]) : NULL,
                               (c >= 2) ? "?" : NULL,
                               (c >= 2) ? ap_escape_uri(p, token[2]) : NULL,
                               (c >= 3) ? "?" : NULL,
                               (c >= 3) ? ap_escape_uri(p, token[3]) : NULL,
                               (c >= 4) ? "?" : NULL,
                               (c >= 4) ? ap_escape_uri(p, token[4]) : NULL,
                               NULL);
        }
    }

    /* Nothing special here. Apply normal escaping. */
    return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
                       ap_escape_uri(p, cp), NULL);
}