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
