static const char *authn_cache_socache(cmd_parms *cmd, void *CFG,
                                       const char *arg)
{
    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP, arg,
                                          AP_SOCACHE_PROVIDER_VERSION);
    if (socache_provider == NULL) {
        errmsg = "Unknown socache provider";
    }
    return errmsg;
}