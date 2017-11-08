static const char *filter_bytype1(cmd_parms *cmd, void *CFG,
                                  const char *pname, const char **types)
{
    const char *rv;
    const char *fname;
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

    rv = add_filter(cmd, CFG, fname, pname, NULL, types);

    /* If it's the first time through, add to filterchain */
    if (rv == NULL && !seen_name) {
        rv = filter_chain(cmd, CFG, fname);
    }
    return rv;
}