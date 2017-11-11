static const char *set_cache_lock_maxage(cmd_parms *parms, void *dummy,
                                    const char *arg)
{
    cache_server_conf *conf;
    apr_int64_t seconds;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    seconds = apr_atoi64(arg);
    if (seconds <= 0) {
        return "CacheLockMaxAge value must be a non-zero positive integer";
    }
    conf->lockmaxage = apr_time_from_sec(seconds);
    conf->lockmaxage_set = 1;
    return NULL;
}