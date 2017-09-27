        reason = "environment variable 'no-cache' is set";
    }
    else if (r->no_cache) {
        /* or we've been asked not to cache it above */
        reason = "r->no_cache present";
    }

    /* Hold the phone. Some servers might allow us to cache a 2xx, but
     * then make their 304 responses non cacheable. This leaves us in a
     * sticky position. If the 304 is in answer to our own conditional
     * request, we cannot send this 304 back to the client because the
     * client isn't expecting it. Instead, our only option is to respect
     * the answer to the question we asked (has it changed, answer was
     * no) and return the cached item to the client, and then respect
     * the uncacheable nature of this 304 by allowing the remove_url
     * filter to kick in and remove the cached entity.
     */
    if (reason && r->status == HTTP_NOT_MODIFIED &&
             cache->stale_handle) {
        apr_bucket_brigade *bb;
        apr_bucket *bkt;
        int status;

        cache->handle = cache->stale_handle;
        info = &cache->handle->cache_obj->info;

        /* Load in the saved status and clear the status line. */
        r->status = info->status;
        r->status_line = NULL;

        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

        r->headers_in = cache->stale_headers;
        status = ap_meets_conditions(r);
        if (status != OK) {
            r->status = status;

            bkt = apr_bucket_flush_create(bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bkt);
        }
        else {
            /* RFC 2616 10.3.5 states that entity headers are not supposed
             * to be in the 304 response.  Therefore, we need to combine the
             * response headers with the cached headers *before* we update
             * the cached headers.
             *
             * However, before doing that, we need to first merge in
             * err_headers_out and we also need to strip any hop-by-hop
             * headers that might have snuck in.
             */
            r->headers_out = ap_cache_cacheable_headers_out(r);

            /* Merge in our cached headers.  However, keep any updated values. */
            cache_accept_headers(cache->handle, r, 1);

            cache->provider->recall_body(cache->handle, r->pool, bb);

            bkt = apr_bucket_eos_create(bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bkt);
        }

        cache->block_response = 1;

        /* we've got a cache conditional hit! tell anyone who cares */
        cache_run_cache_status(
                cache->handle,
                r,
                r->headers_out,
                AP_CACHE_REVALIDATE,
                apr_psprintf(
                        r->pool,
                        "conditional cache hit: 304 was uncacheable though (%s); entity removed",
                        reason));

        /* let someone else attempt to cache */
        cache_remove_lock(conf, cache, r, NULL);

        return ap_pass_brigade(f->next, bb);
    }

    if (reason) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
                "cache: %s not cached. Reason: %s", r->unparsed_uri,
                reason);
