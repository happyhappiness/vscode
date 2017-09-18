     * Caching is forbidden under the following circumstances:
     *
     * - RFC2616 14.9.2 Cache-Control: no-store
     * - Pragma: no-cache
     * - Any requests requiring authorization.
     */
    if (conf->ignorecachecontrol_set == 1 && conf->ignorecachecontrol == 1 && auth == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
            "incoming request is asking for a uncached version of %s, but we know better and are ignoring it", url);
    }
    else {
        if (ap_cache_liststr(cc_in, "no-store", NULL) ||
            ap_cache_liststr(pragma, "no-cache", NULL) || (auth != NULL)) {
            /* delete the previously cached file */
            cache_remove_url(r, cache->types, url);

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                        "cache: no-store forbids caching of %s", url);
            return DECLINED;
        }
    }

    /*
     * Try serve this request from the cache.
     *
     * If no existing cache file
     *   add cache_in filter
     * If stale cache file
     *   If conditional request
     *     add cache_in filter
