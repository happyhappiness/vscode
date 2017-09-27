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
