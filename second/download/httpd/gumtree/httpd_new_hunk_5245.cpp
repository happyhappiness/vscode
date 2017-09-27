     */
    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(in)) {

        rv = cache->provider->store_body(cache->handle, f->r, in, cache->out);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, f->r, APLOGNO(00765)
                    "cache: Cache provider's store_body failed for URI %s", f->r->uri);
            ap_remove_output_filter(f);

            /* give someone else the chance to cache the file */
            cache_remove_lock(conf, cache, f->r, NULL);

            /* give up trying to cache, just step out the way */
