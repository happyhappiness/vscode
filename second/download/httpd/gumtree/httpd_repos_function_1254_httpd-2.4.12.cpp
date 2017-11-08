static const char *set_cache_x_cache(cmd_parms *parms, void *dummy, int flag)
{

    if (parms->path) {
        cache_dir_conf *dconf = (cache_dir_conf *)dummy;

        dconf->x_cache = flag;
        dconf->x_cache_set = 1;

    }
    else {
        cache_server_conf *conf =
            (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                      &cache_module);

        conf->x_cache = flag;
        conf->x_cache_set = 1;

    }

    return NULL;
}