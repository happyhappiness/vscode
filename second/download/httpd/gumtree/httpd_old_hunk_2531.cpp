
            bkt = apr_bucket_flush_create(bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bkt);
        }
        else {
            cache->provider->recall_body(cache->handle, r->pool, bb);
        }

        cache->block_response = 1;

        /* Before returning we need to handle the possible case of an
         * unwritable cache. Rather than leaving the entity in the cache
         * and having it constantly re-validated, now that we have recalled
         * the body it is safe to try and remove the url from the cache.
         */
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                         "cache: updating headers with store_headers failed. "
                         "Removing cached url.");

            rv = cache->provider->remove_url(cache->stale_handle, r->pool);
            if (rv != OK) {
                /* Probably a mod_disk_cache cache area has been (re)mounted
                 * read-only, or that there is a permissions problem.
                 */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: attempt to remove url from cache unsuccessful.");
            }

        }

        /* let someone else attempt to cache */
        ap_cache_remove_lock(conf, r, cache->handle ?
                (char *)cache->handle->cache_obj->key : NULL, NULL);

        return ap_pass_brigade(f->next, bb);
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: store_headers failed");

        ap_remove_output_filter(f);
        ap_cache_remove_lock(conf, r, cache->handle ?
                (char *)cache->handle->cache_obj->key : NULL, NULL);
        return ap_pass_brigade(f->next, in);
    }

    rv = cache->provider->store_body(cache->handle, r, in);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: store_body failed");
        ap_remove_output_filter(f);
        ap_cache_remove_lock(conf, r, cache->handle ?
                (char *)cache->handle->cache_obj->key : NULL, NULL);
        return ap_pass_brigade(f->next, in);
    }

    /* proactively remove the lock as soon as we see the eos bucket */
    ap_cache_remove_lock(conf, r, cache->handle ?
            (char *)cache->handle->cache_obj->key : NULL, in);

    return ap_pass_brigade(f->next, in);
}

/*
 * CACHE_REMOVE_URL filter
 * -----------------------
 *
