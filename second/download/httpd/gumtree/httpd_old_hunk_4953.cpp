                /* Add cache_remove_url filter to this request to remove a
                 * stale cache entry if needed. Also put the current cache
                 * request rec in the filter context, as the request that
                 * is available later during running the filter may be
                 * different due to an internal redirect.
                 */
                cache->remove_url_filter =
                    ap_add_output_filter_handle(cache_remove_url_filter_handle,
                            cache, r, r->connection);

            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                        r, APLOGNO(00760) "Cache locked for url, not caching "
                        "response: %s", r->uri);
