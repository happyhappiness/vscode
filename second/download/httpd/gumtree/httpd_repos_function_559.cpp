static void *merge_remoteip_server_config(apr_pool_t *p, void *globalv,
                                          void *serverv)
{
    remoteip_config_t *global = (remoteip_config_t *) globalv;
    remoteip_config_t *server = (remoteip_config_t *) serverv;
    remoteip_config_t *config;

    config = (remoteip_config_t *) apr_palloc(p, sizeof(*config));
    config->header_name = server->header_name
                        ? server->header_name
                        : global->header_name;
    config->proxies_header_name = server->proxies_header_name
                                ? server->proxies_header_name
                                : global->proxies_header_name;
    config->proxymatch_ip = server->proxymatch_ip
                          ? server->proxymatch_ip
                          : global->proxymatch_ip;
    return config;
}