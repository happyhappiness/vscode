static int is_header_regex(apr_pool_t *p, const char* name)
{
    /* If a Header name contains characters other than:
     *    -,_,[A-Z\, [a-z] and [0-9].
     * assume the header name is a regular expression.
     */
    ap_regex_t *preg = ap_pregcomp(p, "^[-A-Za-z0-9_]*$",
                                   (AP_REG_EXTENDED | AP_REG_NOSUB ));
    ap_assert(preg != NULL);

    if (ap_regexec(preg, name, 0, NULL, 0)) {
        return 1;
    }

    return 0;
}