     */
    if (!cache) {
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
    }

    /* If we've previously processed and set aside part of this
     * response, skip the cacheability checks
     */
    if (cache->saved_brigade != NULL) {
        exp = cache->exp;
        lastmod = cache->lastmod;
        info = cache->info;
    }
    else {

        /*
         * Pass Data to Cache
         * ------------------
         * This section passes the brigades into the cache modules, but only
         * if the setup section (see below) is complete.
         */

        /* have we already run the cachability check and set up the
         * cached file handle? 
         */
        if (cache->in_checked) {
            /* pass the brigades into the cache, then pass them
             * up the filter stack
             */
            rv = cache_write_entity_body(cache->handle, r, in);
            if (rv != APR_SUCCESS) {
                ap_remove_output_filter(f);
            }
            return ap_pass_brigade(f->next, in);
        }

        /*
         * Setup Data in Cache
         * -------------------
         * This section opens the cache entity and sets various caching
         * parameters, and decides whether this URL should be cached at
         * all. This section is* run before the above section.
         */
        info = apr_pcalloc(r->pool, sizeof(cache_info));

        /* read expiry date; if a bad date, then leave it so the client can
         * read it 
         */
        exps = apr_table_get(r->headers_out, "Expires");
        if (exps != NULL) {
            if (APR_DATE_BAD == (exp = apr_date_parse_http(exps))) {
                exps = NULL;
            }
        }
        else {
            exp = APR_DATE_BAD;
        }

        /* read the last-modified date; if the date is bad, then delete it */
        lastmods = apr_table_get(r->headers_out, "Last-Modified");
        if (lastmods != NULL) {
            if (APR_DATE_BAD == (lastmod = apr_date_parse_http(lastmods))) {
                lastmods = NULL;
            }
        }
        else {
            lastmod = APR_DATE_BAD;
        }

        /* read the etag from the entity */
        etag = apr_table_get(r->headers_out, "Etag");

        /*
         * what responses should we not cache?
         *
         * At this point we decide based on the response headers whether it
         * is appropriate _NOT_ to cache the data from the server. There are
         * a whole lot of conditions that prevent us from caching this data.
         * They are tested here one by one to be clear and unambiguous. 
         */

        /* RFC2616 13.4 we are allowed to cache 200, 203, 206, 300, 301 or 410
         * We don't cache 206, because we don't (yet) cache partial responses.
         * We include 304 Not Modified here too as this is the origin server
         * telling us to serve the cached copy.
         */
        if ((r->status != HTTP_OK && r->status != HTTP_NON_AUTHORITATIVE
             && r->status != HTTP_MULTIPLE_CHOICES
             && r->status != HTTP_MOVED_PERMANENTLY
             && r->status != HTTP_NOT_MODIFIED)
            /* if a broken Expires header is present, don't cache it */
            || (exps != NULL && exp == APR_DATE_BAD)
            /* if query string present but no expiration time, don't cache it
             * (RFC 2616/13.9)
             */
            || (r->args && exps == NULL)
            /* if the server said 304 Not Modified but we have no cache
             * file - pass this untouched to the user agent, it's not for us.
             */
            || (r->status == HTTP_NOT_MODIFIED && (NULL == cache->handle))
            /* 200 OK response from HTTP/1.0 and up without a Last-Modified
             * header/Etag 
             */
            /* XXX mod-include clears last_modified/expires/etags - this
             * is why we have an optional function for a key-gen ;-) 
             */
            || (r->status == HTTP_OK && lastmods == NULL && etag == NULL 
                && (conf->no_last_mod_ignore ==0))
            /* HEAD requests */
            || r->header_only
            /* RFC2616 14.9.2 Cache-Control: no-store response
             * indicating do not cache, or stop now if you are
             * trying to cache it */
            || ap_cache_liststr(cc_out, "no-store", NULL)
            /* RFC2616 14.9.1 Cache-Control: private
             * this object is marked for this user's eyes only. Behave
             * as a tunnel.
             */
            || ap_cache_liststr(cc_out, "private", NULL)
            /* RFC2616 14.8 Authorisation:
             * if authorisation is included in the request, we don't cache,
             * but we can cache if the following exceptions are true:
             * 1) If Cache-Control: s-maxage is included
             * 2) If Cache-Control: must-revalidate is included
             * 3) If Cache-Control: public is included
             */
            || (apr_table_get(r->headers_in, "Authorization") != NULL
                && !(ap_cache_liststr(cc_out, "s-maxage", NULL)
                     || ap_cache_liststr(cc_out, "must-revalidate", NULL)
                     || ap_cache_liststr(cc_out, "public", NULL)))
            /* or we've been asked not to cache it above */
            || r->no_cache) {

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: response is not cachable");

            /* remove this object from the cache 
             * BillS Asks.. Why do we need to make this call to remove_url?
             * leave it in for now..
             */
            cache_remove_url(r, cache->types, url);

            /* remove this filter from the chain */
            ap_remove_output_filter(f);

            /* ship the data up the stack */
            return ap_pass_brigade(f->next, in);
        }
        cache->in_checked = 1;
    } /* if cache->saved_brigade==NULL */

    /* Set the content length if known.  We almost certainly do NOT want to
     * cache streams with unknown content lengths in the in-memory cache.
     * Streams with unknown content length should be first cached in the
     * file system. If they are withing acceptable limits, then they can be 
     * moved to the in-memory cache.
