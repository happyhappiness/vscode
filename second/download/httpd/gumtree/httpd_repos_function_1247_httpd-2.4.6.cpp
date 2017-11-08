static const char *set_cache_key_base_url(cmd_parms *parms, void *dummy,
        const char *arg)
{
    cache_server_conf *conf;
    apr_status_t rv;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    conf->base_uri = apr_pcalloc(parms->pool, sizeof(apr_uri_t));
    rv = apr_uri_parse(parms->pool, arg, conf->base_uri);
    if (rv != APR_SUCCESS) {
        return apr_psprintf(parms->pool, "Could not parse '%s' as an URL.", arg);
    }
    else if (!conf->base_uri->scheme && !conf->base_uri->hostname &&
            !conf->base_uri->port_str) {
        return apr_psprintf(parms->pool, "URL '%s' must contain at least one of a scheme, a hostname or a port.", arg);
    }
    conf->base_uri_set = 1;
    return NULL;
}