static const char *authn_cache_socache(cmd_parms *cmd, void *CFG,
                                       const char *arg)
{
    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    const char *sep, *name;

    if (errmsg)
        return errmsg;

    /* Argument is of form 'name:args' or just 'name'. */
    sep = ap_strchr_c(arg, ':');
    if (sep) {
        name = apr_pstrmemdup(cmd->pool, arg, sep - arg);
        sep++;
    }
    else {
        name = arg;
    }

    socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP, name,
                                          AP_SOCACHE_PROVIDER_VERSION);
    if (socache_provider == NULL) {
        errmsg = apr_psprintf(cmd->pool,
                              "Unknown socache provider '%s'. Maybe you need "
                              "to load the appropriate socache module "
                              "(mod_socache_%s?)", arg, arg);
    }
    else {
        errmsg = socache_provider->create(&socache_instance, sep,
                                          cmd->temp_pool, cmd->pool);
    }

    if (errmsg) {
        errmsg = apr_psprintf(cmd->pool, "AuthnCacheSOCache: %s", errmsg);
    }
    return errmsg;
}