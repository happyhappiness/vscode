static const char *set_cache_store_private(cmd_parms *parms, void *dummy,
                                           int flag)
{
    cache_server_conf *conf;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    conf->store_private = flag;
    conf->store_private_set = 1;
    return NULL;
}