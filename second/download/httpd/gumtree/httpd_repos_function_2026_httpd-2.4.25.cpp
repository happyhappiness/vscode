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
    apr_pool_t *rxpool = NULL;

    for (j = 0; j < num_sec; ++j)
    {
        int nmatch = 0;
        int i;
        ap_regmatch_t *pmatch = NULL;

        entry_config = sec_proxy[j];
        entry_proxy = ap_get_module_config(entry_config, &proxy_module);

        if (entry_proxy->r) {

            if (entry_proxy->refs && entry_proxy->refs->nelts) {
                if (!rxpool) {
                    apr_pool_create(&rxpool, r->pool);
                }
                nmatch = entry_proxy->refs->nelts;
                pmatch = apr_palloc(rxpool, nmatch*sizeof(ap_regmatch_t));
            }

            if (ap_regexec(entry_proxy->r, proxyname, nmatch, pmatch, 0)) {
                continue;
            }

            for (i = 0; i < nmatch; i++) {
                if (pmatch[i].rm_so >= 0 && pmatch[i].rm_eo >= 0 &&
                        ((const char **)entry_proxy->refs->elts)[i]) {
                    apr_table_setn(r->subprocess_env,
                            ((const char **)entry_proxy->refs->elts)[i],
                            apr_pstrndup(r->pool,
                                    proxyname + pmatch[i].rm_so,
                                    pmatch[i].rm_eo - pmatch[i].rm_so));
                }
            }
        }

        else if (
            /* XXX: What about case insensitive matching ???
             * Compare regex, fnmatch or string as appropriate
             * If the entry doesn't relate, then continue
             */
            entry_proxy->p_is_fnmatch ? apr_fnmatch(entry_proxy->p,
                    proxyname, 0) :
                    strncmp(proxyname, entry_proxy->p,
                            strlen(entry_proxy->p))) {
            continue;
        }
        per_dir_defaults = ap_merge_per_dir_configs(r->pool, per_dir_defaults,
                                                             entry_config);
    }

    r->per_dir_config = per_dir_defaults;

    if (rxpool) {
        apr_pool_destroy(rxpool);
    }

    return OK;
}