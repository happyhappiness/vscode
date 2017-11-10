static int recurse_args(apr_pool_t *pool, int n, const char *query,
                        apr_dbd_prepared_t *stmt, int offs)
{

    /* we only support %s arguments for now */
    int ret;
    char arg[256];
    regmatch_t matches[3];
    if (regexec(&dbd_freetds_find_arg, query, 3, matches, 0) != 0) {
        /* No more args */
        stmt->nargs = n;
        stmt->taint = apr_palloc(pool, n*sizeof(regex_t*));
        stmt->sz = apr_palloc(pool, n*sizeof(int));
        ret = 0;
    }
    else {
        int i;
        int sz = 0;
        int len = matches[1].rm_eo - matches[1].rm_so - 2;
        if (len > 255) {
            return 9999;
        }

        ret = recurse_args(pool, n+1, query+matches[0].rm_eo,
                           stmt, offs+matches[0].rm_eo);

        memmove(stmt->fmt + offs + matches[1].rm_so,
                stmt->fmt + offs + matches[0].rm_eo-1,
                strlen(stmt->fmt+offs+matches[0].rm_eo)+2);

        /* compile untaint to a regex if found */
        if (matches[1].rm_so == -1) {
            stmt->taint[n] = NULL;
        }
        else {
            strncpy(arg, query+matches[1].rm_so+1,
                    matches[1].rm_eo - matches[1].rm_so - 2);
            arg[matches[1].rm_eo - matches[1].rm_so - 2] = '\0';
            stmt->taint[n] = apr_palloc(pool, sizeof(regex_t));
            if (regcomp(stmt->taint[n], arg, REG_ICASE|REG_EXTENDED) != 0) {
                ++ret;
            }
            else {
                apr_pool_cleanup_register(pool, stmt->taint[n], freetds_regfree,
                                          apr_pool_cleanup_null);
            }
        }

        /* record length if specified */
        for (i=matches[2].rm_so; i<matches[2].rm_eo; ++i) {
            sz = 10*sz + (query[i]-'\0');
        }
    }
    return ret;
}