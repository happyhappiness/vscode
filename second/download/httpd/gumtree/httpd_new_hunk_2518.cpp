     *   add cache_save filter
     * If cached file (OK)
     *   clear filter stack
     *   add cache_out filter
     *   return OK
     */
    rv = cache_select(cache, r);
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
                rv = cache_try_lock(conf, cache, r);
                if (APR_SUCCESS == rv) {

                    /*
                     * Add cache_save filter to cache this request. Choose
                     * the correct filter by checking if we are a subrequest
                     * or not.
                     */
                    if (r->main) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                r, APLOGNO(00749) "Adding CACHE_SAVE_SUBREQ filter for %s",
                                r->uri);
                        cache->save_filter = ap_add_output_filter_handle(
                                cache_save_subreq_filter_handle, cache, r,
                                r->connection);
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                r, APLOGNO(00750) "Adding CACHE_SAVE filter for %s",
                                r->uri);
                        cache->save_filter = ap_add_output_filter_handle(
                                cache_save_filter_handle, cache, r,
                                r->connection);
                    }

                    apr_pool_userdata_setn(cache, CACHE_CTX_KEY, NULL, r->pool);

                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00751)
                            "Adding CACHE_REMOVE_URL filter for %s",
                            r->uri);

                    /* Add cache_remove_url filter to this request to remove a
                     * stale cache entry if needed. Also put the current cache
                     * request rec in the filter context, as the request that
