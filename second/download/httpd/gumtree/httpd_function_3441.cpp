static int cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    int rv = !OK;
    request_rec *r = f->r;
    cache_request_rec *cache;
    cache_server_conf *conf;
    const char *cc_out, *cl;
    const char *exps, *lastmods, *dates, *etag;
    apr_time_t exp, date, lastmod, now;
    apr_off_t size = -1;
    cache_info *info = NULL;
    char *reason;
    apr_pool_t *p;
    apr_bucket *e;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /* Setup cache_request_rec */
    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        /* user likely configured CACHE_SAVE manually; they should really use
         * mod_cache configuration to do that
         */
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
        cache->size = -1;
    }

    reason = NULL;
    p = r->pool;
    /*
     * Pass Data to Cache
     * ------------------
     * This section passes the brigades into the cache modules, but only
     * if the setup section (see below) is complete.
     */
    if (cache->block_response) {
        /* We've already sent down the response and EOS.  So, ignore
         * whatever comes now.
         */
        return APR_SUCCESS;
    }

    /* have we already run the cachability check and set up the
     * cached file handle?
     */
    if (cache->in_checked) {
        /* pass the brigades into the cache, then pass them
         * up the filter stack
         */
        rv = cache->provider->store_body(cache->handle, r, in);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                         "cache: Cache provider's store_body failed!");
            ap_remove_output_filter(f);

            /* give someone else the chance to cache the file */
            ap_cache_remove_lock(conf, r, cache->handle ?
                    (char *)cache->handle->cache_obj->key : NULL, NULL);
        }
        else {

            /* proactively remove the lock as soon as we see the eos bucket */
            ap_cache_remove_lock(conf, r, cache->handle ?
                    (char *)cache->handle->cache_obj->key : NULL, in);

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

    /* read expiry date; if a bad date, then leave it so the client can
     * read it
     */
    exps = apr_table_get(r->err_headers_out, "Expires");
    if (exps == NULL) {
        exps = apr_table_get(r->headers_out, "Expires");
    }
    if (exps != NULL) {
        if (APR_DATE_BAD == (exp = apr_date_parse_http(exps))) {
            exps = NULL;
        }
    }
    else {
        exp = APR_DATE_BAD;
    }

    /* read the last-modified date; if the date is bad, then delete it */
    lastmods = apr_table_get(r->err_headers_out, "Last-Modified");
    if (lastmods == NULL) {
        lastmods = apr_table_get(r->headers_out, "Last-Modified");
    }
    if (lastmods != NULL) {
        lastmod = apr_date_parse_http(lastmods);
        if (lastmod == APR_DATE_BAD) {
            lastmods = NULL;
        }
    }
    else {
        lastmod = APR_DATE_BAD;
    }

    /* read the etag and cache-control from the entity */
    etag = apr_table_get(r->err_headers_out, "Etag");
    if (etag == NULL) {
        etag = apr_table_get(r->headers_out, "Etag");
    }
    cc_out = apr_table_get(r->err_headers_out, "Cache-Control");
    if (cc_out == NULL) {
        cc_out = apr_table_get(r->headers_out, "Cache-Control");
    }

    /*
     * what responses should we not cache?
     *
     * At this point we decide based on the response headers whether it
     * is appropriate _NOT_ to cache the data from the server. There are
     * a whole lot of conditions that prevent us from caching this data.
     * They are tested here one by one to be clear and unambiguous.
     */
    if (r->status != HTTP_OK && r->status != HTTP_NON_AUTHORITATIVE
        && r->status != HTTP_PARTIAL_CONTENT
        && r->status != HTTP_MULTIPLE_CHOICES
        && r->status != HTTP_MOVED_PERMANENTLY
        && r->status != HTTP_NOT_MODIFIED) {
        /* RFC2616 13.4 we are allowed to cache 200, 203, 206, 300, 301 or 410
         * We allow the caching of 206, but a cache implementation might choose
         * to decline to cache a 206 if it doesn't know how to.
         * We include 304 Not Modified here too as this is the origin server
         * telling us to serve the cached copy.
         */
        if (exps != NULL || cc_out != NULL) {
            /* We are also allowed to cache any response given that it has a
             * valid Expires or Cache Control header. If we find a either of
             * those here,  we pass request through the rest of the tests. From
             * the RFC:
             *
             * A response received with any other status code (e.g. status
             * codes 302 and 307) MUST NOT be returned in a reply to a
             * subsequent request unless there are cache-control directives or
             * another header(s) that explicitly allow it. For example, these
             * include the following: an Expires header (section 14.21); a
             * "max-age", "s-maxage",  "must-revalidate", "proxy-revalidate",
             * "public" or "private" cache-control directive (section 14.9).
             */
        }
        else {
            reason = apr_psprintf(p, "Response status %d", r->status);
        }
    }

    if (reason) {
        /* noop */
    }
    else if (exps != NULL && exp == APR_DATE_BAD) {
        /* if a broken Expires header is present, don't cache it */
        reason = apr_pstrcat(p, "Broken expires header: ", exps, NULL);
    }
    else if (exp != APR_DATE_BAD && exp < r->request_time)
    {
        /* if a Expires header is in the past, don't cache it */
        reason = "Expires header already expired, not cacheable";
    }
    else if (!conf->ignorequerystring && r->parsed_uri.query && exps == NULL &&
             !ap_cache_liststr(NULL, cc_out, "max-age", NULL) &&
             !ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)) {
        /* if a query string is present but no explicit expiration time,
         * don't cache it (RFC 2616/13.9 & 13.2.1)
         */
        reason = "Query string present but no explicit expiration time";
    }
    else if (r->status == HTTP_NOT_MODIFIED &&
             !cache->handle && !cache->stale_handle) {
        /* if the server said 304 Not Modified but we have no cache
         * file - pass this untouched to the user agent, it's not for us.
         */
        reason = "HTTP Status 304 Not Modified";
    }
    else if (r->status == HTTP_OK && lastmods == NULL && etag == NULL
             && (exps == NULL) && (conf->no_last_mod_ignore ==0) &&
             !ap_cache_liststr(NULL, cc_out, "max-age", NULL) &&
             !ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)) {
        /* 200 OK response from HTTP/1.0 and up without Last-Modified,
         * Etag, Expires, Cache-Control:max-age, or Cache-Control:s-maxage
         * headers.
         */
        /* Note: mod-include clears last_modified/expires/etags - this
         * is why we have an optional function for a key-gen ;-)
         */
        reason = "No Last-Modified, Etag, Expires, Cache-Control:max-age or Cache-Control:s-maxage headers";
    }
    else if (r->header_only && !cache->stale_handle) {
        /* Forbid HEAD requests unless we have it cached already */
        reason = "HTTP HEAD request";
    }
    else if (!conf->store_nostore &&
             ap_cache_liststr(NULL, cc_out, "no-store", NULL)) {
        /* RFC2616 14.9.2 Cache-Control: no-store response
         * indicating do not cache, or stop now if you are
         * trying to cache it.
         */
        /* FIXME: The Cache-Control: no-store could have come in on a 304,
         * FIXME: while the original request wasn't conditional.  IOW, we
         * FIXME:  made the the request conditional earlier to revalidate
         * FIXME: our cached response.
         */
        reason = "Cache-Control: no-store present";
    }
    else if (!conf->store_private &&
             ap_cache_liststr(NULL, cc_out, "private", NULL)) {
        /* RFC2616 14.9.1 Cache-Control: private response
         * this object is marked for this user's eyes only. Behave
         * as a tunnel.
         */
        /* FIXME: See above (no-store) */
        reason = "Cache-Control: private present";
    }
    else if (apr_table_get(r->headers_in, "Authorization") != NULL
             && !(ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)
                  || ap_cache_liststr(NULL, cc_out, "must-revalidate", NULL)
                  || ap_cache_liststr(NULL, cc_out, "public", NULL))) {
        /* RFC2616 14.8 Authorisation:
         * if authorisation is included in the request, we don't cache,
         * but we can cache if the following exceptions are true:
         * 1) If Cache-Control: s-maxage is included
         * 2) If Cache-Control: must-revalidate is included
         * 3) If Cache-Control: public is included
         */
        reason = "Authorization required";
    }
    else if (ap_cache_liststr(NULL,
                              apr_table_get(r->headers_out, "Vary"),
                              "*", NULL)) {
        reason = "Vary header contains '*'";
    }
    else if (apr_table_get(r->subprocess_env, "no-cache") != NULL) {
        reason = "environment variable 'no-cache' is set";
    }
    else if (r->no_cache) {
        /* or we've been asked not to cache it above */
        reason = "r->no_cache present";
    }

    if (reason) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: %s not cached. Reason: %s", r->unparsed_uri,
                     reason);

        /* remove this filter from the chain */
        ap_remove_output_filter(f);

        /* remove the lock file unconditionally */
        ap_cache_remove_lock(conf, r, cache->handle ?
                (char *)cache->handle->cache_obj->key : NULL, NULL);

        /* ship the data up the stack */
        return ap_pass_brigade(f->next, in);
    }

    /* Make it so that we don't execute this path again. */
    cache->in_checked = 1;

    /* Set the content length if known.
     */
    cl = apr_table_get(r->err_headers_out, "Content-Length");
    if (cl == NULL) {
        cl = apr_table_get(r->headers_out, "Content-Length");
    }
    if (cl) {
        char *errp;
        if (apr_strtoff(&size, cl, &errp, 10) || *errp || size < 0) {
            cl = NULL; /* parse error, see next 'if' block */
        }
    }

    if (!cl) {
        /* if we don't get the content-length, see if we have all the
         * buckets and use their length to calculate the size
         */
        int all_buckets_here=0;
        size=0;
        for (e = APR_BRIGADE_FIRST(in);
             e != APR_BRIGADE_SENTINEL(in);
             e = APR_BUCKET_NEXT(e))
        {
            if (APR_BUCKET_IS_EOS(e)) {
                all_buckets_here=1;
                break;
            }
            if (APR_BUCKET_IS_FLUSH(e)) {
                continue;
            }
            if (e->length == (apr_size_t)-1) {
                break;
            }
            size += e->length;
        }
        if (!all_buckets_here) {
            size = -1;
        }
    }

    /* remember content length to check response size against later */
    cache->size = size;

    /* It's safe to cache the response.
     *
     * There are two possiblities at this point:
     * - cache->handle == NULL. In this case there is no previously
     * cached entity anywhere on the system. We must create a brand
     * new entity and store the response in it.
     * - cache->stale_handle != NULL. In this case there is a stale
     * entity in the system which needs to be replaced by new
     * content (unless the result was 304 Not Modified, which means
     * the cached entity is actually fresh, and we should update
     * the headers).
     */

    /* Did we have a stale cache entry that really is stale?
     *
     * Note that for HEAD requests, we won't get the body, so for a stale
     * HEAD request, we don't remove the entity - instead we let the
     * CACHE_REMOVE_URL filter remove the stale item from the cache.
     */
    if (cache->stale_handle) {
        if (r->status == HTTP_NOT_MODIFIED) {
            /* Oh, hey.  It isn't that stale!  Yay! */
            cache->handle = cache->stale_handle;
            info = &cache->handle->cache_obj->info;
            rv = OK;
        }
        else if (!r->header_only) {
            /* Oh, well.  Toss it. */
            cache->provider->remove_entity(cache->stale_handle);
            /* Treat the request as if it wasn't conditional. */
            cache->stale_handle = NULL;
            /*
             * Restore the original request headers as they may be needed
             * by further output filters like the byterange filter to make
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
        info->date = apr_date_parse_http(dates);
    }
    else {
        info->date = APR_DATE_BAD;
    }

    now = apr_time_now();
    if (info->date == APR_DATE_BAD) {  /* No, or bad date */
        /* no date header (or bad header)! */
        info->date = now;
    }
    date = info->date;

    /* set response_time for HTTP/1.1 age calculations */
    info->response_time = now;

    /* get the request time */
    info->request_time = r->request_time;

    /* check last-modified date */
    if (lastmod != APR_DATE_BAD && lastmod > date) {
        /* if it's in the future, then replace by date */
        lastmod = date;
        lastmods = dates;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                     r->server,
                     "cache: Last modified is in the future, "
                     "replacing with now");
    }

    /* if no expiry date then
     *   if Cache-Control: max-age
     *      expiry date = date + max-age
     *   else if lastmod
     *      expiry date = date + min((date - lastmod) * factor, maxexpire)
     *   else
     *      expire date = date + defaultexpire
     */
    if (exp == APR_DATE_BAD) {
        char *max_age_val;

        if (ap_cache_liststr(r->pool, cc_out, "max-age", &max_age_val) &&
            max_age_val != NULL) {
            apr_int64_t x;

            errno = 0;
            x = apr_atoi64(max_age_val);
            if (errno) {
                x = conf->defex;
            }
            else {
                x = x * MSEC_ONE_SEC;
            }
            if (x < conf->minex) {
                x = conf->minex;
            }
            if (x > conf->maxex) {
                x = conf->maxex;
            }
            exp = date + x;
        }
        else if ((lastmod != APR_DATE_BAD) && (lastmod < date)) {
            /* if lastmod == date then you get 0*conf->factor which results in
             * an expiration time of now. This causes some problems with
             * freshness calculations, so we choose the else path...
             */
            apr_time_t x = (apr_time_t) ((date - lastmod) * conf->factor);

            if (x < conf->minex) {
                x = conf->minex;
            }
            if (x > conf->maxex) {
                x = conf->maxex;
            }
            exp = date + x;
        }
        else {
            exp = date + conf->defex;
        }
    }
    info->expire = exp;

    /* We found a stale entry which wasn't really stale. */
    if (cache->stale_handle) {
        /* Load in the saved status and clear the status line. */
        r->status = info->status;
        r->status_line = NULL;

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
        ap_cache_accept_headers(cache->handle, r, 1);
    }

    /* Write away header information to cache. It is possible that we are
     * trying to update headers for an entity which has already been cached.
     *
     * This may fail, due to an unwritable cache area. E.g. filesystem full,
     * permissions problems or a read-only (re)mount. This must be handled
     * later.
     */
    rv = cache->provider->store_headers(cache->handle, r, info);

    /* Did we just update the cached headers on a revalidated response?
     *
     * If so, we can now decide what to serve to the client.  This is done in
     * the same way as with a regular response, but conditions are now checked
     * against the cached or merged response headers.
     */
    if (cache->stale_handle) {
        apr_bucket_brigade *bb;
        apr_bucket *bkt;
        int status;

        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

        /* Restore the original request headers and see if we need to
         * return anything else than the cached response (ie. the original
         * request was conditional).
         */
        r->headers_in = cache->stale_headers;
        status = ap_meets_conditions(r);
        if (status != OK) {
            r->status = status;

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