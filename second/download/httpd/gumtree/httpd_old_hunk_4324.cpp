
        return APR_SUCCESS;
    }

    if (reason) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
                "cache: %s not cached. Reason: %s", r->unparsed_uri,
                reason);

        /* we've got a cache miss! tell anyone who cares */
        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                reason);

        /* remove this filter from the chain */
