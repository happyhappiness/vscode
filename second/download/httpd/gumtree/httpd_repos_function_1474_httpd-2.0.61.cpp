static int cache_url_handler(request_rec *r, int lookup)
{
    apr_status_t rv;
    const char *pragma, *auth;
    apr_uri_t uri;
    char *url;
    char *path;
    cache_provider_list *providers;
    cache_info *info;
    cache_request_rec *cache;
    cache_server_conf *conf;
    apr_bucket_brigade *out;

    /* Delay initialization until we know we are handling a GET */
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    uri = r->parsed_uri;
    url = r->unparsed_uri;
    path = uri.path;
    info = NULL;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(providers = ap_cache_get_providers(r, conf, path))) {
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
    pragma = apr_table_get(r->headers_in, "Pragma");
    auth = apr_table_get(r->headers_in, "Authorization");

    /* first things first - does the request allow us to return
     * cached information at all? If not, just decline the request.
     *
     * Note that there is a big difference between not being allowed
     * to cache a request (no-store) and not being allowed to return
     * a cached request without revalidation (max-age=0).
     *
     * Caching is forbidden under the following circumstances:
     *
     * - RFC2616 14.9.2 Cache-Control: no-store
     * - Pragma: no-cache
     * - Any requests requiring authorization.
     */
    if (conf->ignorecachecontrol == 1 && auth == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "incoming request is asking for a uncached version of "
                     "%s, but we know better and are ignoring it", url);
    }
    else {
        if (ap_cache_liststr(NULL, pragma, "no-cache", NULL) ||
            auth != NULL) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no-cache or authorization forbids caching "
                         "of %s", url);
            return DECLINED;
        }
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
    rv = cache_select_url(r, url);
    if (rv != OK) {
        if (rv == DECLINED) {
            if (!lookup) {
                /* add cache_save filter to cache this request */
                ap_add_output_filter_handle(cache_save_filter_handle, NULL, r,
                                            r->connection);
            }
        }
        else {
            /* error */
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while checking for cached "
                         "file by %s cache", cache->provider_name);
        }
        return DECLINED;
    }

    /* We have located a suitable cache file now. */
    info = &(cache->handle->cache_obj->info);

    if (info && info->lastmod) {
        ap_update_mtime(r, info->lastmod);
    }

    rv = ap_meets_conditions(r);
    if (rv != OK) {
        /* Return cached status. */
        return rv;
    }

    /* If we're a lookup, we can exit now instead of serving the content. */
    if (lookup) {
        return OK;
    }

    /* Serve up the content */

    /* We are in the quick handler hook, which means that no output
     * filters have been set. So lets run the insert_filter hook.
     */
    ap_run_insert_filter(r);
    ap_add_output_filter_handle(cache_out_filter_handle, NULL,
                                r, r->connection);

    /* kick off the filter stack */
    out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    rv = ap_pass_brigade(r->output_filters, out);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "cache: error returned while trying to return %s "
                     "cached data", 
                     cache->provider_name);
        return rv;
    }

    return OK;
}