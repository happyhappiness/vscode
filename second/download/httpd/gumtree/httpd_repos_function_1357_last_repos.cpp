static const char *set_cache_socache(cmd_parms *cmd, void *in_struct_ptr,
        const char *arg)
{
    cache_socache_conf *conf = ap_get_module_config(cmd->server->module_config,
            &cache_socache_module);
    cache_socache_provider_conf *provider = conf->provider
            = apr_pcalloc(cmd->pool, sizeof(cache_socache_provider_conf));

    const char *err = NULL, *sep, *name;

    /* Argument is of form 'name:args' or just 'name'. */
    sep = ap_strchr_c(arg, ':');
    if (sep) {
        name = apr_pstrmemdup(cmd->pool, arg, sep - arg);
        sep++;
        provider->args = sep;
    }
    else {
        name = arg;
    }

    provider->socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP,
            name, AP_SOCACHE_PROVIDER_VERSION);
    if (provider->socache_provider == NULL) {
        err = apr_psprintf(cmd->pool,
                    "Unknown socache provider '%s'. Maybe you need "
                    "to load the appropriate socache module "
                    "(mod_socache_%s?)", name, name);
    }
    return err;
}