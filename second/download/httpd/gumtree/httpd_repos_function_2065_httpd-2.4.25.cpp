static void ap_add_per_proxy_conf(server_rec *s, ap_conf_vector_t *dir_config)
{
    proxy_server_conf *sconf = ap_get_module_config(s->module_config,
                                                    &proxy_module);
    void **new_space = (void **)apr_array_push(sconf->sec_proxy);

    *new_space = dir_config;
}