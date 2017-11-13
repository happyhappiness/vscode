static int cache_handler(request_rec *r)
{
    apr_status_t rv;
    cache_provider_list *providers;
    cache_request_rec *cache;
    apr_bucket_brigade *out;
    apr_bucket *e;
    ap_filter_t *next;
    ap_filter_rec_t *cache_out_handle;
    ap_filter_rec_t *cache_save_handle;
    cache_server_conf *conf;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /* only run if the quick handler is disabled */
    if (conf->quick) {
        return DECLINED;
    }

    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(providers = cache_get_providers(r, conf, r->parsed_uri))) {
        return DECLINED;
    }

    /* make space for the per request config */
    cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
    cache->size = -1;
    cache->out = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    /* save away the possible providers */
    cache->providers = providers;

    /*
     * Are we allowed to serve cached info at all?
     */
    if (!ap_cache_check_no_store(cache, r)) {
        return DECLINED;
    }

    /* Are we PUT/POST/DELETE? If so, prepare to invalidate the cached entities.
     */
    switch (r->method_number) {
    case M_PUT:
    case M_POST:
    case M_DELETE:
    {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02463)
                "PUT/POST/DELETE: Adding CACHE_INVALIDATE filter for %s",
                r->uri);

        /* Add cache_invalidate filter to this request to force a
         * cache entry to be invalidated if the response is
         * ultimately successful (2xx).
         */
        ap_add_output_filter_handle(
                cache_invalidate_filter_handle, cache, r,
                r->connection);

        return DECLINED;
    }
    case M_GET: {
        break;
    }
    default : {

        ap_log_rerror(
                APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02464) "cache: Method '%s' not cacheable by mod_cache, ignoring: %s", r->method, r->uri);

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
    rv = cache_select(cache, r);
    if (rv != OK) {
        if (rv == DECLINED) {

            /* try to obtain a cache lock at this point. if we succeed,
             * we are the first to try and cache this url. if we fail,
             * it means someone else is already trying to cache this
             * url, and we should just let the request through to the
             * backend without any attempt to cache. this stops
             * duplicated simultaneous attempts to cache an entity.
             */
            rv = cache_try_lock(conf, cache, r);
            if (APR_SUCCESS == rv) {

                /*
                 * Add cache_save filter to cache this request. Choose
                 * the correct filter by checking if we are a subrequest
                 * or not.
                 */
                if (r->main) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00756) "Adding CACHE_SAVE_SUBREQ filter for %s",
                            r->uri);
                    cache_save_handle = cache_save_subreq_filter_handle;
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00757) "Adding CACHE_SAVE filter for %s",
                            r->uri);
                    cache_save_handle = cache_save_filter_handle;
                }
                ap_add_output_filter_handle(cache_save_handle, cache, r,
                        r->connection);

                /*
                 * Did the user indicate the precise location of the
                 * CACHE_SAVE filter by inserting the CACHE filter as a
                 * marker?
                 *
                 * If so, we get cunning and replace CACHE with the
                 * CACHE_SAVE filter. This has the effect of inserting
                 * the CACHE_SAVE filter at the precise location where
                 * the admin wants to cache the content. All filters that
                 * lie before and after the original location of the CACHE
                 * filter will remain in place.
                 */
                if (cache_replace_filter(r->output_filters,
                        cache_filter_handle, cache_save_handle,
                        ap_get_input_filter_handle("SUBREQ_CORE"))) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00758) "Replacing CACHE with CACHE_SAVE "
                            "filter for %s", r->uri);
                }

                /* save away the save filter stack */
                cache->save_filter = cache_get_filter(r->output_filters,
                        cache_save_filter_handle);

                apr_pool_userdata_setn(cache, CACHE_CTX_KEY, NULL, r->pool);

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00759)
                        "Adding CACHE_REMOVE_URL filter for %s",
                        r->uri);

                /* Add cache_remove_url filter to this request to remove a
                 * stale cache entry if needed. Also put the current cache
                 * request rec in the filter context, as the request that
                 * is available later during running the filter may be
                 * different due to an internal redirect.
                 */
                cache->remove_url_filter
                        = ap_add_output_filter_handle(
                                cache_remove_url_filter_handle, cache, r,
                                r->connection);

            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                        r, APLOGNO(00760) "Cache locked for url, not caching "
                        "response: %s", r->uri);
            }
        }
        else {
            /* error */
            return rv;
        }
        return DECLINED;
    }

    /* we've got a cache hit! tell everyone who cares */
    cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_HIT,
            "cache hit");

    rv = ap_meets_conditions(r);
    if (rv != OK) {
        return rv;
    }

    /* Serve up the content */

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
    ap_add_output_filter_handle(cache_out_handle, cache, r, r->connection);

    /*
     * Did the user indicate the precise location of the CACHE_OUT filter by
     * inserting the CACHE filter as a marker?
     *
     * If so, we get cunning and replace CACHE with the CACHE_OUT filters.
     * This has the effect of inserting the CACHE_OUT filter at the precise
     * location where the admin wants to cache the content. All filters that
     * lie *after* the original location of the CACHE filter will remain in
     * place.
     */
    if (cache_replace_filter(r->output_filters, cache_filter_handle,
            cache_out_handle, ap_get_input_filter_handle("SUBREQ_CORE"))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                r, APLOGNO(00761) "Replacing CACHE with CACHE_OUT filter for %s",
                r->uri);
    }

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
    e = apr_bucket_eos_create(out->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(out, e);
    return ap_pass_brigade_fchk(r, out, "cache(%s): ap_pass_brigade returned",
                                cache->provider_name);
}