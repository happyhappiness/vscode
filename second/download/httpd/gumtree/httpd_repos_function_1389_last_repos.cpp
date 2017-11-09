int cache_use_early_url(request_rec *r)
{
    cache_server_conf *conf;

    if (r->proxyreq == PROXYREQ_PROXY) {
        return 1;
    }

    conf = ap_get_module_config(r->server->module_config, &cache_module);
    if (conf->quick) {
        return 1;
    }

    return 0;
}