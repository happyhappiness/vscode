static const char *authn_cache_setprovider(cmd_parms *cmd, void *CFG,
                                           const char *arg)
{
    authn_cache_dircfg *cfg = CFG;
    if (cfg->providers == NULL) {
        cfg->providers = apr_array_make(cmd->pool, 4, sizeof(const char*));
    }
    APR_ARRAY_PUSH(cfg->providers, const char*) = arg;
    configured = 1;
    return NULL;
}