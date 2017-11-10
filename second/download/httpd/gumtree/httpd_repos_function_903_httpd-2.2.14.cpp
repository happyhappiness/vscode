static int cache_url_handler(request_rec *r, int lookup)
{
    apr_status_t rv;
    const char *auth;
    cache_provider_list *providers;
    cache_request_rec *cache;
    cache_server_conf *conf;
    apr_bucket_brigade *out;
    ap_filter_t *next;
    ap_filter_rec_t *cache_out_handle;

    /* Delay initialization until we know we are handling a GET */
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(providers = ap_cache_get_providers(r, conf, r->parsed_uri))) {
        return DECLINED;
    }

    /* make space for the per request config */
    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
    }

    /* save away the possible providers */
    cache->providers = providers;

    /*
     * Are we allowed to serve cached info at all?
     */

    /* find certain cache controlling headers */
    auth = apr_table_get(r->headers_in, "Authorization");

    /* First things first - does the request allow us to return
     * cached information at all? If not, just decline the request.
     */
    if (auth) {
        return DECLINED;
    }

    /*
     * Try to serve this request from the cache.
     *
     * If no existing cache file (DECLINED)
     *   add cache_save filter
     * If cached file (OK)
     *   clear filter stack
     *   add cache_out filter
     *   return OK
     */
    rv = cache_select(r);
    if (rv != OK) {
        if (rv == DECLINED) {
            if (!lookup) {

                /*
                 * Add cache_save filter to cache this request. Choose
                 * the correct filter by checking if we are a subrequest
                 * or not.
                 */
                if (r->main) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                 r->server,
                                 "Adding CACHE_SAVE_SUBREQ filter for %s",
                                 r->uri);
                    ap_add_output_filter_handle(cache_save_subreq_filter_handle,
                                                NULL, r, r->connection);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                 r->server, "Adding CACHE_SAVE filter for %s",
                                 r->uri);
                    ap_add_output_filter_handle(cache_save_filter_handle,
                                                NULL, r, r->connection);
                }

                ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                             "Adding CACHE_REMOVE_URL filter for %s",
                             r->uri);

                /* Add cache_remove_url filter to this request to remove a
                 * stale cache entry if needed. Also put the current cache
                 * request rec in the filter context, as the request that
                 * is available later during running the filter maybe
                 * different due to an internal redirect.
                 */
                cache->remove_url_filter =
                    ap_add_output_filter_handle(cache_remove_url_filter_handle,
                                                cache, r, r->connection);
            }
            else {
                if (cache->stale_headers) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                 r->server, "Restoring request headers for %s",
                                 r->uri);

                    r->headers_in = cache->stale_headers;
                }

                /* Delete our per-request configuration. *