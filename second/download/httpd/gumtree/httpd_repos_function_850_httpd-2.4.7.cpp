const char *ssl_cmd_SSLStaplingCache(cmd_parms *cmd,
                                    void *dcfg,
                                    const char *arg)
{
    SSLModConfigRec *mc = myModConfig(cmd->server);
    const char *err, *sep, *name;

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    /* Argument is of form 'name:args' or just 'name'. */
    sep = ap_strchr_c(arg, ':');
    if (sep) {
        name = apr_pstrmemdup(cmd->pool, arg, sep - arg);
        sep++;
    }
    else {
        name = arg;
    }

    /* Find the provider of given name. */
    mc->stapling_cache = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP,
                                            name,
                                            AP_SOCACHE_PROVIDER_VERSION);
    if (mc->stapling_cache) {
        /* Cache found; create it, passing anything beyond the colon. */
        err = mc->stapling_cache->create(&mc->stapling_cache_context,
                                         sep, cmd->temp_pool,
                                         cmd->pool);
    }
    else {
        apr_array_header_t *name_list;
        const char *all_names;

        /* Build a comma-separated list of all registered provider
         * names: */
        name_list = ap_list_provider_names(cmd->pool,
                                           AP_SOCACHE_PROVIDER_GROUP,
                                           AP_SOCACHE_PROVIDER_VERSION);
        all_names = apr_array_pstrcat(cmd->pool, name_list, ',');

        err = apr_psprintf(cmd->pool, "'%s' stapling cache not supported "
                           "(known names: %s) Maybe you need to load the "
                           "appropriate socache module (mod_socache_%s?)",
                           name, all_names, name);
    }

    if (err) {
        return apr_psprintf(cmd->pool, "SSLStaplingCache: %s", err);
    }

    return NULL;
}