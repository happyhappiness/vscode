static apr_status_t cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    int rv = !OK;
    request_rec *r = f->r;
    cache_request_rec *cache = (cache_request_rec *)f->ctx;
    cache_server_conf *conf;
    cache_dir_conf *dconf;
    cache_control_t control;
    const char *cc_out, *cl, *pragma;
    const char *exps, *lastmods, *dates, *etag;
    apr_time_t exp, date, lastmod, now;
    apr_off_t size = -1;
    cache_info *info = NULL;
    const char *reason;
    apr_pool_t *p;
    apr_bucket *e;
    apr_table_t *headers;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /* Setup cache_request_rec */
    if (!cache) {
        /* user likely configured CACHE_SAVE manually; they should really use
         * mod_cache configuration to do that
         */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00767)
                "CACHE/CACHE_SAVE filter enabled while caching is disabled, ignoring");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, in);
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
    cc_out = cache_table_getm(r->pool, r->err_headers_out, "Cache-Control");
    pragma = cache_table_getm(r->pool, r->err_headers_out, "Pragma");
    headers = r->err_headers_out;
    if (!cc_out && !pragma) {
        cc_out = cache_table_getm(r->pool, r->headers_out, "Cache-Control");
        pragma = cache_table_getm(r->pool, r->headers_out, "Pragma");
        headers = r->headers_out;
    }

    /* Have we received a 304 response without any headers at all? Fall back to
     * the original headers in the original cached request.
     */
    if (r->status == HTTP_NOT_MODIFIED && cache->stale_handle && !cc_out
            && !pragma) {
        cc_out = cache_table_getm(r->pool, cache->stale_handle->resp_hdrs,
                "Cache-Control");
        pragma = cache_table_getm(r->pool, cache->stale_handle->resp_hdrs,
                "Pragma");
    }

    /* Parse the cache control header */
    memset(&control, 0, sizeof(cache_control_t));
    ap_cache_control(r, &control, cc_out, pragma, headers);

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
    else if (!dconf->store_expired && exp != APR_DATE_BAD
            && exp < r->request_time) {
        /* if a Expires header is in the past, don't cache it */
        reason = "Expires header already expired; not cacheable";
    }
    else if (!dconf->store_expired && (control.must_revalidate
            || control.proxy_revalidate) && (!control.s_maxage_value
            || (!control.s_maxage && !control.max_age_value)) && lastmods
            == NULL && etag == NULL) {
        /* if we're already stale, but can never revalidate, don't cache it */
        reason
                = "s-maxage or max-age zero and no Last-Modified or Etag; not cacheable";
    }
    else if (!conf->ignorequerystring && r->parsed_uri.query && exps == NULL
            && !control.max_age && !control.s_maxage) {
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
    else if (r->status == HTTP_OK && lastmods == NULL && etag == NULL && (exps
            == NULL) && (dconf->no_last_mod_ignore == 0) && !control.max_age
            && !control.s_maxage) {
        /* 200 OK response from HTTP/1.0 and up without Last-Modified,
         * Etag, Expires, Cache-Control:max-age, or Cache-Control:s-maxage
         * headers.
         */
        /* Note: mod-include clears last_modified/expires/etags - this
         * is why we have an optional function for a key-gen ;-)
         */
        reason = "No Last-Modified; Etag; Expires; Cache-Control:max-age or Cache-Control:s-maxage headers";
    }
    else if (!dconf->store_nostore && control.no_store) {
        /* RFC2616 14.9.2 Cache-Control: no-store response
         * indicating do not cache, or stop now if you are
         * trying to cache it.
         */
        reason = "Cache-Control: no-store present";
    }
    else if (!dconf->store_private && control.private) {
        /* RFC2616 14.9.1 Cache-Control: private response
         * this object is marked for this user's eyes only. Behave
         * as a tunnel.
         */
        reason = "Cache-Control: private present";
    }
    else if (apr_table_get(r->headers_in, "Authorization")
            && !(control.s_maxage || control.must_revalidate
                    || control.proxy_revalidate || control.public)) {
        /* RFC2616 14.8 Authorisation:
         * if authorisation is included in the request, we don't cache,
         * but we can cache if the following exceptions are true:
         * 1) If Cache-Control: s-maxage is included
         * 2) If Cache-Control: must-revalidate is included
         * 3) If Cache-Control: public is included
         */
        reason = "Authorization required";
    }
    else if (ap_find_token(NULL, apr_table_get(r->headers_out, "Vary"), "*")) {
        reason = "Vary header contains '*'";
    }
    else if (apr_table_get(r->subprocess_env, "no-cache") != NULL) {
        reason = "environment variable 'no-cache' is set";
    }
    else if (r->no_cache) {
        /* or we've been asked not to cache it above */
        reason = "r->no_cache present";
    }
    else if (cache->stale_handle
            && APR_DATE_BAD
                    != (date = apr_date_parse_http(
                            apr_table_get(r->headers_out, "Date")))
            && date < cache->stale_handle->cache_obj->info.date) {

        /**
         * 13.12 Cache Replacement:
         *
         * Note: a new response that has an older Date header value than
         * existing cached responses is not cacheable.
         */
        reason = "updated entity is older than cached entity";

        /* while this response is not cacheable, the previous response still is */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00770)
                "cache: Removing CACHE_REMOVE_URL filter.");
        ap_remove_output_filter(cache->remove_url_filter);
    }
    else if (r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {
        apr_table_t *left = cache->stale_handle->resp_hdrs;
        apr_table_t *right = r->headers_out;

        /* and lastly, contradiction checks for revalidated responses
         * as per RFC2616 Section 10.3.5
         */
        if (((reason = cache_header_cmp(r->pool, left, right, "Allow")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Encoding")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Language")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Length")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Location")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-MD5")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Range")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Content-Type")))
                || ((reason = cache_header_cmp(r->pool, left, right, "Expires")))
                || ((reason = cache_header_cmp(r->pool, left, right, "ETag")))
                || ((reason = cache_header_cmp(r->pool, left, right,
                        "Last-Modified")))) {
            /* contradiction: 304 Not Modified, but entity header modified */
        }
    }

    /**
     * Enforce RFC2616 Section 10.3.5, just in case. We caught any
     * inconsistencies above.
     *
     * If the conditional GET used a strong cache validator (see section
     * 13.3.3), the response SHOULD NOT include other entity-headers.
     * Otherwise (i.e., the conditional GET used a weak validator), the
     * response MUST NOT include other entity-headers; this prevents
     * inconsistencies between cached entity-bodies and updated headers.
     */
    if (r->status == HTTP_NOT_MODIFIED) {
        apr_table_unset(r->headers_out, "Allow");
        apr_table_unset(r->headers_out, "Content-Encoding");
        apr_table_unset(r->headers_out, "Content-Language");
        apr_table_unset(r->headers_out, "Content-Length");
        apr_table_unset(r->headers_out, "Content-MD5");
        apr_table_unset(r->headers_out, "Content-Range");
        apr_table_unset(r->headers_out, "Content-Type");
        apr_table_unset(r->headers_out, "Last-Modified");
    }

    /* Hold the phone. Some servers might allow us to cache a 2xx, but
     * then make their 304 responses non cacheable. RFC2616 says this:
     *
     * If a 304 response indicates an entity not currently cached, then
     * the cache MUST disregard the response and repeat the request
     * without the conditional.
     *
     * A 304 response with contradictory headers is technically a
     * different entity, to be safe, we remove the entity from the cache.
     */
    if (reason && r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {

        ap_log_rerror(
                APLOG_MARK, APLOG_INFO, 0, r, APLOGNO() "cache: %s responded with an uncacheable 304, retrying the request. Reason: %s", r->unparsed_uri, reason);

        /* we've got a cache conditional miss! tell anyone who cares */
        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                apr_psprintf(r->pool,
                        "conditional cache miss: 304 was uncacheable, entity removed: %s",
                        reason));

        /* remove the cached entity immediately, we might cache it again */
        ap_remove_output_filter(cache->remove_url_filter);
        cache_remove_url(cache, r);

        /* let someone else attempt to cache */
        cache_remove_lock(conf, cache, r, NULL);

        /* remove this filter from the chain */
        ap_remove_output_filter(f);

        /* retry without the conditionals */
        apr_table_unset(r->headers_in, "If-Match");
        apr_table_unset(r->headers_in, "If-Modified-Since");
        apr_table_unset(r->headers_in, "If-None-Match");
        apr_table_unset(r->headers_in, "If-Range");
        apr_table_unset(r->headers_in, "If-Unmodified-Since");

        ap_internal_redirect(r->uri, r);

        return APR_SUCCESS;
    }

    if (reason) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
                "cache: %s not cached. Reason: %s", r->unparsed_uri,
                reason);

        /* we've got a cache miss! tell anyone who cares */
        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                reason);

        /* remove this filter from the chain */
        ap_remove_output_filter(f);

        /* remove the lock file unconditionally */
        cache_remove_lock(conf, cache, r, NULL);

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
     */
    if (cache->stale_handle) {
        if (r->status == HTTP_NOT_MODIFIED) {
            /* Oh, hey.  It isn't that stale!  Yay! */
            cache->handle = cache->stale_handle;
            info = &cache->handle->cache_obj->info;
            rv = OK;
        }
        else {
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

    /* no cache handle, create a new entity */
    if (!cache->handle) {
        rv = cache_create_entity(cache, r, size, in);
        info = apr_pcalloc(r->pool, sizeof(cache_info));
        /* We only set info->status upon the initial creation. */
        info->status = r->status;
    }

    if (rv != OK) {
        /* we've got a cache miss! tell anyone who cares */
        cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                "cache miss: cache unwilling to store response");

        /* Caching layer declined the opportunity to cache the response */
        ap_remove_output_filter(f);
        cache_remove_lock(conf, cache, r, NULL);
        return ap_pass_brigade(f->next, in);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00769)
            "cache: Caching url: %s", r->unparsed_uri);

    /* We are actually caching this response. So it does not
     * make sense to remove this entity any more.
     */
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00770)
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

    /* store away the previously parsed cache control headers */
    memcpy(&info->control, &control, sizeof(cache_control_t));

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
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0,
                r, APLOGNO(00771) "cache: Last modified is in the future, "
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

        if (control.max_age) {
            apr_int64_t x;

            errno = 0;
            x = control.max_age_value;
            if (errno) {
                x = dconf->defex;
            }
            else {
                x = x * MSEC_ONE_SEC;
            }
            if (x < dconf->minex) {
                x = dconf->minex;
            }
            if (x > dconf->maxex) {
                x = dconf->maxex;
            }
            exp = date + x;
        }
        else if ((lastmod != APR_DATE_BAD) && (lastmod < date)) {
            /* if lastmod == date then you get 0*conf->factor which results in
             * an expiration time of now. This causes some problems with
             * freshness calculations, so we choose the else path...
             */
            apr_time_t x = (apr_time_t) ((date - lastmod) * dconf->factor);

            if (x < dconf->minex) {
                x = dconf->minex;
            }
            if (x > dconf->maxex) {
                x = dconf->maxex;
            }
            exp = date + x;
        }
        else {
            exp = date + dconf->defex;
        }
    }
    info->expire = exp;

    /* We found a stale entry which wasn't really stale. */
    if (cache->stale_handle) {

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
        /* take output, overlay on top of cached */
        cache_accept_headers(cache->handle, r, r->headers_out,
                cache->handle->resp_hdrs, 1);
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

        /* Load in the saved status and clear the status line. */
        r->status = info->status;
        r->status_line = NULL;

        /* We're just saving response headers, so we are done. Commit
         * the response at this point, unless there was a previous error.
         */
        if (rv == APR_SUCCESS) {
            rv = cache->provider->commit_entity(cache->handle, r);
        }

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