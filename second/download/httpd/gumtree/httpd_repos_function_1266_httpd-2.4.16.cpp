static const char *set_cache_ignore_querystring(cmd_parms *parms, void *dummy,
                                                int flag)
{
    cache_server_conf *conf;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    conf->ignorequerystring = flag;
    conf->ignorequerystring_set = 1;
    return NULL;
}