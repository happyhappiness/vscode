             * the correct decisions.
             */
            r->headers_in = cache->stale_headers;
        }
    }

    /* no cache handle, create a new entity only for non-HEAD requests */
    if (!cache->handle && !r->header_only) {
        rv = cache_create_entity(r, size);
        info = apr_pcalloc(r->pool, sizeof(cache_info));
        /* We only set info->status upon the initial creation. */
        info->status = r->status;
    }

    if (rv != OK) {
        /* Caching layer declined the opportunity to cache the response */
        ap_remove_output_filter(f);
        ap_cache_remove_lock(conf, r, cache->handle ?
                (char *)cache->handle->cache_obj->key : NULL, NULL);
        return ap_pass_brigade(f->next, in);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "cache: Caching url: %s", r->unparsed_uri);

    /* We are actually caching this response. So it does not
     * make sense to remove this entity any more.
     */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "cache: Removing CACHE_REMOVE_URL filter.");
    ap_remove_output_filter(cache->remove_url_filter);

    /*
     * We now want to update the cache file header information with
     * the new date, last modified, expire and content length and write
     * it away to our cache file. First, we determine these values from
     * the response, using heuristics if appropriate.
     *
     * In addition, we make HTTP/1.1 age calculations and write them away
     * too.
     */

    /* Read the date. Generate one if one is not supplied */
    dates = apr_table_get(r->err_headers_out, "Date");
    if (dates == NULL) {
        dates = apr_table_get(r->headers_out, "Date");
    }
    if (dates != NULL) {
