        /* We've already sent down the response and EOS.  So, ignore
         * whatever comes now.
         */
        return APR_SUCCESS;
    }

    /* have we already run the cacheability check and set up the
     * cached file handle?
     */
    if (cache->in_checked) {
        return cache_save_store(f, in, conf, cache);
    }

    /*
     * Setup Data in Cache
     * -------------------
     * This section opens the cache entity and sets various caching
     * parameters, and decides whether this URL should be cached at
     * all. This section is* run before the above section.
     */

    dconf = ap_get_module_config(r->per_dir_config, &cache_module);

    /* RFC2616 13.8 Errors or Incomplete Response Cache Behavior:
     * If a cache receives a 5xx response while attempting to revalidate an
     * entry, it MAY either forward this response to the requesting client,
     * or act as if the server failed to respond. In the latter case, it MAY
     * return a previously received response unless the cached entry
     * includes the "must-revalidate" cache-control directive (see section
     * 14.9).
     *
     * This covers the case where an error was generated behind us, for example
     * by a backend server via mod_proxy.
     */
    if (dconf->stale_on_error && r->status >= HTTP_INTERNAL_SERVER_ERROR) {

        ap_remove_output_filter(cache->remove_url_filter);

        if (cache->stale_handle
                && !cache->stale_handle->cache_obj->info.control.must_revalidate
                && !cache->stale_handle->cache_obj->info.control.proxy_revalidate) {
            const char *warn_head;

            /* morph the current save filter into the out filter, and serve from
             * cache.
             */
            cache->handle = cache->stale_handle;
            if (r->main) {
                f->frec = cache_out_subreq_filter_handle;
            }
            else {
                f->frec = cache_out_filter_handle;
            }

            r->headers_out = cache->stale_handle->resp_hdrs;

            ap_set_content_type(r, apr_table_get(
                    cache->stale_handle->resp_hdrs, "Content-Type"));

            /* add a revalidation warning */
            warn_head = apr_table_get(r->err_headers_out, "Warning");
            if ((warn_head == NULL) || ((warn_head != NULL)
                    && (ap_strstr_c(warn_head, "111") == NULL))) {
                apr_table_mergen(r->err_headers_out, "Warning",
                        "111 Revalidation failed");
            }

            cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_HIT,
                    apr_psprintf(r->pool,
                            "cache hit: %d status; stale content returned",
                            r->status));

            /* give someone else the chance to cache the file */
            cache_remove_lock(conf, cache, f->r, NULL);

            /* pass brigade to our morphed out filter */
            return ap_pass_brigade(f, in);
        }
    }

    /* read expiry date; if a bad date, then leave it so the client can
     * read it
     */
    exps = apr_table_get(r->err_headers_out, "Expires");
    if (exps == NULL) {
        exps = apr_table_get(r->headers_out, "Expires");
    }
    if (exps != NULL) {
        exp = apr_date_parse_http(exps);
    }
    else {
        exp = APR_DATE_BAD;
    }

    /* read the last-modified date; if the date is bad, then delete it */
