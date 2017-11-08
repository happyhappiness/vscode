static const char *filter_bytype1(cmd_parms *cmd, void *CFG,
                                  const char *pname, const char *type)
{
    char *etype;
    char *p;
    const char *rv;
    const char *fname;
    const char *expr;
    int seen_name = 0;
    mod_filter_cfg *cfg = CFG;

    /* construct fname from name */
    fname = apr_pstrcat(cmd->pool, "BYTYPE:", pname, NULL);

    /* check whether this is already registered, in which case
     * it's already in the filter chain
     */
    if (apr_hash_get(cfg->live_filters, fname, APR_HASH_KEY_STRING)) {
        seen_name = 1;
    }

    /* build expression: "$content-type = /^type/"
     * Need to escape slashes in content-type
     */
    p = etype = apr_palloc(cmd->temp_pool, 2*strlen(type)+1);
    do {
        if (*type == '/') {
            *p++ = '\\';
        }
        *p++ = *type++;
    } while (*type);
    *p = 0;
    expr = apr_psprintf(cmd->temp_pool, "$content-type = /^%s/", etype);

    rv = filter_provider(cmd, CFG, fname, pname, expr);

    /* If it's the first time through, add to filterchain */
    if (rv == NULL && !seen_name) {
        rv = filter_chain(cmd, CFG, fname);
    }
    return rv;
}