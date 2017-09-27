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
