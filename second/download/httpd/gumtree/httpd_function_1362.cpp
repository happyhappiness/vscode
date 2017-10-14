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

                /* try to obtain a cache lock at this point. if we succeed,
                 * we are the first to try and cache this url. if we fail,
                 * it means someone else is already trying to cache this
                 * url, and we should just let the request through to the
                 * backend without any attempt to cache. this stops
                 * duplicated simultaneous attempts to cache an entity.
                 */
                rv = ap_cache_try_lock(conf, r, NULL);
                if (APR_SUCCESS == rv) {

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
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, rv,
                                 r->server, "Cache locked for url, not caching "
                                 "response: %s", r->uri);
                }
            }
            else {
                if (cache->stale_headers) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                 r->server, "Restoring request headers for %s",
                                 r->uri);

                    r->headers_in = cache->stale_headers;
                }

                /* Delete our per-request configuration. */
                ap_set_module_config(r->request_config, &cache_module, NULL);
            }
        }
        else {
            /* error */
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while checking for cached "
                         "file by '%s' cache", cache->provider_name);
        }
        return DECLINED;
    }

    /* if we are a lookup, we are exiting soon one way or another; Restore
     * the headers. */
    if (lookup) {
        if (cache->stale_headers) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                         "Restoring request headers.");
            r->headers_in = cache->stale_headers;
        }

        /* Delete our per-request configuration. */
        ap_set_module_config(r->request_config, &cache_module, NULL);
    }

    rv = ap_meets_conditions(r);
    if (rv != OK) {
        /* If we are a lookup, we have to return DECLINED as we have no
         * way of knowing if we will be able to serve the content.
         */
        if (lookup) {
            return DECLINED;
        }

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

    /*
     * Add cache_out filter to serve this request. Choose
     * the correct filter by checking if we are a subrequest
     * or not.
     */
    if (r->main) {
        cache_out_handle = cache_out_subreq_filter_handle;
    }
    else {
        cache_out_handle = cache_out_filter_handle;
    }
    ap_add_output_filter_handle(cache_out_handle, NULL, r, r->connection);

    /*
     * Remove all filters that are before the cache_out filter. This ensures
     * that we kick off the filter stack with our cache_out filter being the
     * first in the chain. This make sense because we want to restore things
     * in the same manner as we saved them.
     * There may be filters before our cache_out filter, because
     *
     * 1. We call ap_set_content_type during cache_select. This causes
     *    Content-Type specific filters to be added.
     * 2. We call the insert_filter hook. This causes filters e.g. like
     *    the ones set with SetOutputFilter to be added.
     */
    next = r->output_filters;
    while (next && (next->frec != cache_out_handle)) {
        ap_remove_output_filter(next);
        next = next->next;
    }

    /* kick off the filter stack */
    out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    rv = ap_pass_brigade(r->output_filters, out);
    if (rv != APR_SUCCESS) {
        if (rv != AP_FILTER_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while trying to return %s "
                         "cached data",
                         cache->provider_name);
        }
        return rv;
    }

    return OK;
}