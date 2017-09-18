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
     *   If fresh cache file
     *     clear filter stack
     *     add cache_out filter
     *     return OK
     *   If stale cache file
     *       add cache_conditional filter (which updates cache)
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

    /* RFC2616 13.2 - Check cache object expiration */
    cache->fresh = ap_cache_check_freshness(cache, r);

    /* What we have in our cache isn't fresh. */
    if (!cache->fresh) {
        /* If our stale cached response was conditional... */
        if (!lookup && ap_cache_request_is_conditional(r)) {
            info = &(cache->handle->cache_obj->info);

            /* fudge response into a conditional */
            if (info && info->etag) {
                /* if we have a cached etag */
                apr_table_set(r->headers_in, "If-None-Match", info->etag);
            }
            else if (info && info->lastmods) {
                /* if we have a cached IMS */
                apr_table_set(r->headers_in, "If-Modified-Since",
                              info->lastmods);
            }
        }

        /* Add cache_conditional_filter to see if we can salvage
         * later.
         */
        ap_add_output_filter_handle(cache_conditional_filter_handle,
                                    NULL, r, r->connection);
        return DECLINED;
    }

    /* fresh data available */

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

/*
 * CACHE_OUT filter
 * ----------------
 *
