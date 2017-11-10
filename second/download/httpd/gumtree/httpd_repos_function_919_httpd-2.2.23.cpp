static const char *set_cache_ignore_no_last_mod(cmd_parms *parms, void *dummy,
                                                int flag)
{
    cache_server_conf *conf;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    conf->no_last_mod_ignore = flag;
    conf->no_last_mod_ignore_set = 1;
    return NULL;

}