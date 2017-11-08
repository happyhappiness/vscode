int cache_select(cache_request_rec *cache, request_rec *r)
{
    cache_provider_list *list;
    apr_status_t rv;
    cache_handle_t *h;

    if (!cache) {
        /* This should never happen */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r, APLOGNO(00693)
                "cache: No cache request information available for key"
                " generation");
        return DECLINED;
    }

    /* if no-cache, we can't serve from the cache, but we may store to the
     * cache.
     */
    if (!ap_cache_check_no_cache(cache, r)) {
        return DECLINED;
    }

    if (!cache->key) {
        rv = cache_generate_key(r, r->pool, &cache->key);
        if (rv != APR_SUCCESS) {
            return DECLINED;
        }
    }

    /* go through the cache types till we get a match */
    h = apr_palloc(r->pool, sizeof(cache_handle_t));

    list = cache->providers;

    while (list) {
        switch ((rv = list->provider->open_entity(h, r, cache->key))) {
        case OK: {
            char *vary = NULL;
            int mismatch = 0;
            char *last = NULL;

            if (list->provider->recall_headers(h, r) != APR_SUCCESS) {
                /* try again with next cache type */
                list = list->next;
                continue;
            }

            /*
             * Check Content-Negotiation - Vary
             *
             * At this point we need to make sure that the object we found in
             * the cache is the same object that would be delivered to the
             * client, when the effects of content negotiation are taken into
             * effect.
             *
             * In plain english, we want to make sure that a language-negotiated
             * document in one language is not given to a client asking for a
             * language negotiated document in a different language by mistake.
             *
             * This code makes the assumption that the storage manager will
             * cache the req_hdrs if the response contains a Vary
             * header.
             *
             * RFC2616 13.6 and 14.44 describe the Vary mechanism.
             */
            vary = cache_strqtok(
                    apr_pstrdup(r->pool,
                            cache_table_getm(r->pool, h->resp_hdrs, "Vary")),
                    CACHE_SEPARATOR, &last);
            while (vary) {
                const char *h1, *h2;

                /*
                 * is this header in the request and the header in the cached
                 * request identical? If not, we give up and do a straight get
                 */
                h1 = cache_table_getm(r->pool, r->headers_in, vary);
                h2 = cache_table_getm(r->pool, h->req_hdrs, vary);
                if (h1 == h2) {
                    /* both headers NULL, so a match - do nothing */
                }
                else if (h1 && h2 && !strcmp(h1, h2)) {
                    /* both headers exist and are equal - do nothing */
                }
                else {
                    /* headers do not match, so Vary failed */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00694) "cache_select(): Vary header mismatch.");
                    mismatch = 1;
                    break;
                }
                vary = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
            }

            /* no vary match, try next provider */
            if (mismatch) {
                /* try again with next cache type */
                list = list->next;
                continue;
            }

            cache->provider = list->provider;
            cache->provider_name = list->provider_name;

            /*
             * RFC2616 13.3.4 Rules for When to Use Entity Tags and Last-Modified
             * Dates: An HTTP/1.1 caching proxy, upon receiving a conditional request
             * that includes both a Last-Modified date and one or more entity tags as
             * cache validators, MUST NOT return a locally cached response to the
             * client unless that cached response is consistent with all of the
             * conditional header fields in the request.
             */
            if (ap_condition_if_match(r, h->resp_hdrs) == AP_CONDITION_NOMATCH
                    || ap_condition_if_unmodified_since(r, h->resp_hdrs)
                            == AP_CONDITION_NOMATCH
                    || ap_condition_if_none_match(r, h->resp_hdrs)
                            == AP_CONDITION_NOMATCH
                    || ap_condition_if_modified_since(r, h->resp_hdrs)
                            == AP_CONDITION_NOMATCH
                    || ap_condition_if_range(r, h->resp_hdrs) == AP_CONDITION_NOMATCH) {
                mismatch = 1;
            }

            /* Is our cached response fresh enough? */
            if (mismatch || !cache_check_freshness(h, cache, r)) {
                const char *etag, *lastmod;

                /* Cache-Control: only-if-cached and revalidation required, try
                 * the next provider
                 */
                if (cache->control_in.only_if_cached) {
                    /* try again with next cache type */
                    list = list->next;
                    continue;
                }

                /* set aside the stale entry for accessing later */
                cache->stale_headers = apr_table_copy(r->pool,
                        r->headers_in);
                cache->stale_handle = h;

                /* if no existing conditionals, use conditionals of our own */
                if (!mismatch) {

                    ap_log_rerror(
                            APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00695) "Cached response for %s isn't fresh. Adding "
                            "conditional request headers.", r->uri);

                    /* Remove existing conditionals that might conflict with ours */
                    apr_table_unset(r->headers_in, "If-Match");
                    apr_table_unset(r->headers_in, "If-Modified-Since");
                    apr_table_unset(r->headers_in, "If-None-Match");
                    apr_table_unset(r->headers_in, "If-Range");
                    apr_table_unset(r->headers_in, "If-Unmodified-Since");

                    etag = apr_table_get(h->resp_hdrs, "ETag");
                    lastmod = apr_table_get(h->resp_hdrs, "Last-Modified");

                    if (etag || lastmod) {
                        /* If we have a cached etag and/or Last-Modified add in
                         * our own conditionals.
                         */

                        if (etag) {
                            apr_table_set(r->headers_in, "If-None-Match", etag);
                        }

                        if (lastmod) {
                            apr_table_set(r->headers_in, "If-Modified-Since",
                                    lastmod);
                        }

                        /*
                         * Do not do Range requests with our own conditionals: If
                         * we get 304 the Range does not matter and otherwise the
                         * entity changed and we want to have the complete entity
                         */
                        apr_table_unset(r->headers_in, "Range");

                    }

                }

                /* ready to revalidate, pretend we were never here */
                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            cache_accept_headers(h, r, h->resp_hdrs, r->headers_out, 0);

            cache->handle = h;
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
            list = list->next;
            continue;
        }
        default: {
            /* oo-er! an error */
            return rv;
        }
        }
    }

    /* if Cache-Control: only-if-cached, and not cached, return 504 */
    if (cache->control_in.only_if_cached) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00696)
                "cache: 'only-if-cached' requested and no cached entity, "
                "returning 504 Gateway Timeout for: %s", r->uri);
        return HTTP_GATEWAY_TIME_OUT;
    }

    return DECLINED;
}