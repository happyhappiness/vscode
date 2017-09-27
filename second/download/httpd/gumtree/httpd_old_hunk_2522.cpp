                 * the CACHE_SAVE filter at the precise location where
                 * the admin wants to cache the content. All filters that
                 * lie before and after the original location of the CACHE
                 * filter will remain in place.
                 */
                if (cache_replace_filter(r->output_filters,
                        cache_filter_handle, cache_save_handle)) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r->server, "Replacing CACHE with CACHE_SAVE "
                            "filter for %s", r->uri);
                }

                ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                        "Adding CACHE_REMOVE_URL filter for %s",
                        r->uri);

                /* Add cache_remove_url filter to this request to remove a
                 * stale cache entry if needed. Also put the current cache
                 * request rec in the filter context, as the request that
