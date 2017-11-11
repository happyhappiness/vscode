static void *create_remoteip_server_config(apr_pool_t *p, server_rec *s)
{
    remoteip_config_t *config = apr_pcalloc(p, sizeof *config);
    /* config->header_name = NULL;
     * config->proxies_header_name = NULL;
     */
    return config;
}