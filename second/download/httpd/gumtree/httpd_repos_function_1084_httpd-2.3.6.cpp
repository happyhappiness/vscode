static const char *set_cache_factor(cmd_parms *parms, void *dummy,
                                    const char *arg)
{
    cache_server_conf *conf;
    double val;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    if (sscanf(arg, "%lg", &val) != 1) {
        return "CacheLastModifiedFactor value must be a float";
    }
    conf->factor = val;
    conf->factor_set = 1;
    return NULL;
}