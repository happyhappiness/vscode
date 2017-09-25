    if (DECLINED == rv) {
        if (!lookup) {
            /* no existing cache file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no cache - add cache_in filter and DECLINE");
            /* add cache_in filter to cache this request */
            ap_add_output_filter_handle(cache_in_filter_handle, NULL, r,
                                        r->connection);
        }
        return DECLINED;
    }
    else if (OK == rv) {
        /* RFC2616 13.2 - Check cache object expiration */
        cache->fresh = ap_cache_check_freshness(cache, r);
