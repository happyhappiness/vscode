static int proxy_walk(request_rec *r)
{
    proxy_server_conf *sconf = ap_get_module_config(r->server->module_config,
                                                    &proxy_module);
    ap_conf_vector_t *per_dir_defaults = r->server->lookup_defaults;
    ap_conf_vector_t **sec_proxy = (ap_conf_vector_t **) sconf->sec_proxy->elts;
    ap_conf_vector_t *entry_config;
    proxy_dir_conf *entry_proxy;
    int num_sec = sconf->sec_proxy->nelts;
    /* XXX: shouldn't we use URI here?  Canonicalize it first?
     * Pass over "proxy:" prefix
     */
    const char *proxyname = r->filename + 6;
    int j;

    for (j = 0; j < num_sec; ++j)
    {
        entry_config = sec_proxy[j];
        entry_proxy = ap_get_module_config(entry_config, &proxy_module);

        /* XXX: What about case insensitive matching ???
         * Compare regex, fnmatch or string as appropriate
         * If the entry doesn't relate, then continue
         */
        if (entry_proxy->r
              ? ap_regexec(entry_proxy->r, proxyname, 0, NULL, 0)
              : (entry_proxy->p_is_fnmatch
                   ? apr_fnmatch(entry_proxy->p, proxyname, 0)
                   : strncmp(proxyname, entry_proxy->p,
                                        strlen(entry_proxy->p)))) {
            continue;
        }
        per_dir_defaults = ap_merge_per_dir_configs(r->pool, per_dir_defaults,
                                                             entry_config);
    }

    r->per_dir_config = per_dir_defaults;

    return OK;
}