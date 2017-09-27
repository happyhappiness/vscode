
            bkt = apr_bucket_flush_create(bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bkt);
        }
        else {
            cache->provider->recall_body(cache->handle, r->pool, bb);

            bkt = apr_bucket_eos_create(bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bkt);
        }

        cache->block_response = 1;

        /* Before returning we need to handle the possible case of an
         * unwritable cache. Rather than leaving the entity in the cache
         * and having it constantly re-validated, now that we have recalled
         * the body it is safe to try and remove the url from the cache.
         */
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(00772)
                    "cache: updating headers with store_headers failed. "
                    "Removing cached url.");

            rv = cache->provider->remove_url(cache->stale_handle, r);
            if (rv != OK) {
                /* Probably a mod_cache_disk cache area has been (re)mounted
                 * read-only, or that there is a permissions problem.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(00773)
                        "cache: attempt to remove url from cache unsuccessful.");
            }

            /* we've got a cache conditional hit! tell anyone who cares */
            cache_run_cache_status(cache->handle, r, r->headers_out,
                    AP_CACHE_REVALIDATE,
                    "conditional cache hit: entity refresh failed");

        }
        else {

            /* we've got a cache conditional hit! tell anyone who cares */
            cache_run_cache_status(cache->handle, r, r->headers_out,
                    AP_CACHE_REVALIDATE,
                    "conditional cache hit: entity refreshed");

        }

        /* let someone else attempt to cache */
        cache_remove_lock(conf, cache, r, NULL);

        return ap_pass_brigade(f->next, bb);
    }

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(00774)
                "cache: store_headers failed");

        /* we've got a cache miss! tell anyone who cares */
        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                "cache miss: store_headers failed");

        ap_remove_output_filter(f);
        cache_remove_lock(conf, cache, r, NULL);
        return ap_pass_brigade(f->next, in);
    }

    /* we've got a cache miss! tell anyone who cares */
    cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
            "cache miss: attempting entity save");

    return cache_save_store(f, in, conf, cache);
}

/*
 * CACHE_REMOVE_URL filter
 * -----------------------
 *
