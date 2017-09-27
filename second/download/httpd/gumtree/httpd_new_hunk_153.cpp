    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(types = ap_cache_get_cachetype(r, conf, path))) {
        return DECLINED;
    }

    urllen = strlen(url);
    if (urllen > MAX_URL_LENGTH) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: URL exceeds length threshold: %s", url);
        return DECLINED;
