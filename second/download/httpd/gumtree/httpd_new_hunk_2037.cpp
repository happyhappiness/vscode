    return DECLINED;
}

apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
                                        char**key)
{
    cache_server_conf *conf;
    cache_request_rec *cache;
    char *port_str, *hn, *lcs;
    const char *hostname, *scheme;
    int i;

    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        /* This should never happen */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache: No cache request information available for key"
                     " generation");
        *key = "";
        return APR_EGENERAL;
    }
    if (cache->key) {
        /*
         * We have been here before during the processing of this request.
         * So return the key we already have.
         */
        *key = apr_pstrdup(p, cache->key);
        return APR_SUCCESS;
    }

    /*
     * Get the module configuration. We need this for the CacheIgnoreQueryString
     * option below.
     */
    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /*
     * Use the canonical name to improve cache hit rate, but only if this is
     * not a proxy request or if this is a reverse proxy request.
     * We need to handle both cases in the same manner as for the reverse proxy
     * case we have the following situation:
     *
