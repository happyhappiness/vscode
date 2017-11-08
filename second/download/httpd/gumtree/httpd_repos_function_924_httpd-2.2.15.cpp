static const char *set_cache_defex(cmd_parms *parms, void *dummy,
                                   const char *arg)
{
    cache_server_conf *conf;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    conf->defex = (apr_time_t) (atol(arg) * MSEC_ONE_SEC);
    conf->defex_set = 1;
    return NULL;
}