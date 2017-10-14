static apr_status_t cache_invalidate_filter(ap_filter_t *f,
                                            apr_bucket_brigade *in)
{
    request_rec *r = f->r;
    cache_request_rec *cache;

    /* Setup cache_request_rec */
    cache = (cache_request_rec *) f->ctx;

    if (!cache) {
        /* user likely configured CACHE_INVALIDATE manually; they should really
         * use mod_cache configuration to do that. So:
         * 1. Remove ourselves
         * 2. Do nothing and bail out
         */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02465)
                "cache: CACHE_INVALIDATE enabled unexpectedly: %s", r->uri);
    }
    else {

        if (r->status > 299) {

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02466)
                    "cache: response status to '%s' method is %d (>299), not invalidating cached entity: %s", r->method, r->status, r->uri);

        }
        else {

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02467)
                    "cache: Invalidating all cached entities in response to '%s' request for %s",
                    r->method, r->uri);

            cache_invalidate(cache, r);

            /* we've got a cache invalidate! tell everyone who cares */
            cache_run_cache_status(cache->handle, r, r->headers_out,
                    AP_CACHE_INVALIDATE, apr_psprintf(r->pool,
                            "cache invalidated by %s", r->method));

        }

    }

    /* remove ourselves */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}