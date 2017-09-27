    /* remove ourselves */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}

/*
 * CACHE_INVALIDATE filter
 * -----------------------
 *
 * This filter gets added in the quick handler should a PUT, POST or DELETE
 * method be detected. If the response is successful, we must invalidate any
 * cached entity as per RFC2616 section 13.10.
 *
 * CACHE_INVALIDATE has to be a protocol filter to ensure that is run even if
 * the response is a canned error message, which removes the content filters
 * from the chain.
 *
 * CACHE_INVALIDATE expects cache request rec within its context because the
 * request this filter runs on can be different from the one whose cache entry
 * should be removed, due to internal redirects.
 */
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

/*
 * CACHE filter
 * ------------
 *
 * This filter can be optionally inserted into the filter chain by the admin as
 * a marker representing the precise location within the filter chain where
 * caching is to be performed.
