static int is_header_regex(apr_pool_t *p, const char* name)
{
    /* If a Header name contains characters other than:
     *    -,_,[A-Z\, [a-z] and [0-9].
     * assume the header name is a regular expression.
     */
    if (ap_regexec(is_header_regex_regex, name, 0, NULL, 0)) {
        return 1;
    }

    return 0;
}