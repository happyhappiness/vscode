    if (!cache) {
        /* user likely configured CACHE_REMOVE_URL manually; they should really
         * use mod_cache configuration to do that. So:
         * 1. Remove ourselves
         * 2. Do nothing and bail out
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: CACHE_REMOVE_URL enabled unexpectedly");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, in);
    }

    /* Now remove this cache entry from the cache */
    cache_remove_url(cache, r->pool);

    /* remove ourselves */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}

