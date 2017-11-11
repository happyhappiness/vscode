static const char *set_cache_complete(cmd_parms *parms, void *dummy,
                                      const char *arg)
{
    cache_server_conf *conf;
    int val;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    if (sscanf(arg, "%u", &val) != 1) {
        return "CacheForceCompletion value must be a percentage";
    }
    conf->complete = val;
    conf->complete_set = 1;
    return NULL;
}