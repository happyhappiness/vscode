static const char *set_cache_lock_path(cmd_parms *parms, void *dummy,
                                    const char *arg)
{
    cache_server_conf *conf;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);

    conf->lockpath = ap_server_root_relative(parms->pool, arg);
    if (!conf->lockpath) {
        return apr_pstrcat(parms->pool, "Invalid CacheLockPath path ",
                           arg, NULL);
    }
    conf->lockpath_set = 1;
    return NULL;
}