static const char *add_filter(cmd_parms *cmd, void *CFG,
                              const char *fname, const char *pname,
                              const char *expr, const char **types)
{
    mod_filter_cfg *cfg = CFG;
    ap_filter_provider_t *provider;
    const char *c;
    ap_filter_rec_t* frec;
    ap_filter_rec_t* provider_frec;
    ap_expr_info_t *node;
    const char *err = NULL;

    /* fname has been declared with DeclareFilter, so we can look it up */
    frec = apr_hash_get(cfg->live_filters, fname, APR_HASH_KEY_STRING);

    /* or if provider is mod_filter itself, we can also look it up */
    if (!frec) {
        c = filter_declare(cmd, CFG, fname, NULL);
        if ( c ) {
            return c;
        }
        frec = apr_hash_get(cfg->live_filters, fname, APR_HASH_KEY_STRING);
    }

    if (!frec) {
        return apr_psprintf(cmd->pool, "Undeclared smart filter %s", fname);
    }

    /* if provider has been registered, we can look it up */
    provider_frec = ap_get_output_filter_handle(pname);
    if (!provider_frec) {
        return apr_psprintf(cmd->pool, "Unknown filter provider %s", pname);
    }
    provider = apr_palloc(cmd->pool, sizeof(ap_filter_provider_t));
    if (expr) {
        node = ap_expr_parse_cmd(cmd, expr, 0, &err, NULL);
        if (err) {
            return apr_pstrcat(cmd->pool,
                               "Error parsing FilterProvider expression:", err,
                               NULL);
        }
        provider->expr = node;
        provider->types = NULL;
    }
    else {
        provider->types = types;
        provider->expr = NULL;
    }
    provider->frec = provider_frec;
    provider->next = frec->providers;
    frec->providers = provider;
    return NULL;
}