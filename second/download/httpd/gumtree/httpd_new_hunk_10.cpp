    void *sconf = r->server->module_config;
    cache_server_conf *conf =
        (cache_server_conf *) ap_get_module_config(sconf, &cache_module);
    void *scache = r->request_config;
    cache_request_rec *cache =
        (cache_request_rec *) ap_get_module_config(scache, &cache_module);
    apr_bucket *split_point = NULL;


    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "cache: running CACHE_IN filter");

    /* check first whether running this filter has any point or not */
