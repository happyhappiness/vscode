static const char *authn_cache_socache(cmd_parms *cmd, void *CFG,
                                       const char *arg)
{
    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (errmsg)
        return errmsg;
    socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP, arg,
                                          AP_SOCACHE_PROVIDER_VERSION);
    if (socache_provider == NULL) {
        errmsg = apr_psprintf(cmd->pool,
                              "Unknown socache provider '%s'. Maybe you need "
                              "to load the appropriate socache module "
                              "(mod_socache_%s?)", arg, arg);
    }
    return errmsg;
}