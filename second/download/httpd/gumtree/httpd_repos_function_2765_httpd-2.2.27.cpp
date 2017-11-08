static const char *dbd_untaint(apr_pool_t *pool, regex_t *rx, const char *val)
{
    regmatch_t match[1];
    if (rx == NULL) {
        /* no untaint expression */
        return val;
    }
    if (regexec(rx, val, 1, match, 0) == 0) {
        return apr_pstrndup(pool, val+match[0].rm_so,
                            match[0].rm_eo - match[0].rm_so);
    }
    return "";
}