static const char *dav_cmd_dav(cmd_parms *cmd, void *config, const char *arg1)
{
    dav_dir_conf *conf = (dav_dir_conf *)config;

    if (strcasecmp(arg1, "on") == 0) {
        conf->provider_name = DAV_DEFAULT_PROVIDER;
    }
    else if (strcasecmp(arg1, "off") == 0) {
        conf->provider_name = NULL;
        conf->provider = NULL;
    }
    else {
        conf->provider_name = apr_pstrdup(cmd->pool, arg1);
    }

    if (conf->provider_name != NULL) {
        /* lookup and cache the actual provider now */
        conf->provider = dav_lookup_provider(conf->provider_name);

        if (conf->provider == NULL) {
            /* by the time they use it, the provider should be loaded and
               registered with us. */
            return apr_psprintf(cmd->pool,
                                "Unknown DAV provider: %s",
                                conf->provider_name);
        }
    }

    return NULL;
}