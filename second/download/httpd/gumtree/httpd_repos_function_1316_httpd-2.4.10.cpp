static apr_status_t destroy_cache(void *data)
{
    server_rec *s = data;
    cache_socache_conf *conf =
            ap_get_module_config(s->module_config, &cache_socache_module);
    if (conf->provider && conf->provider->socache_instance) {
        conf->provider->socache_provider->destroy(
                conf->provider->socache_instance, s);
        conf->provider->socache_instance = NULL;
    }
    return APR_SUCCESS;
}