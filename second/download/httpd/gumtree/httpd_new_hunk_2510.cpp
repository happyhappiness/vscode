                }
                else if (h1 && h2 && !strcmp(h1, h2)) {
                    /* both headers exist and are equal - do nothing */
                }
                else {
                    /* headers do not match, so Vary failed */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00694) "cache_select_url(): Vary header mismatch.");
                    mismatch = 1;
                }
            }

            /* no vary match, try next provider */
            if (mismatch) {
                /* try again with next cache type */
                list = list->next;
                continue;
            }

            cache->provider = list->provider;
            cache->provider_name = list->provider_name;

            /* Is our cached response fresh enough? */
            fresh = cache_check_freshness(h, cache, r);
            if (!fresh) {
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

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00695)
                        "Cached response for %s isn't fresh.  Adding/replacing "
                        "conditional request headers.", r->uri);

                /* We can only revalidate with our own conditionals: remove the
                 * conditions from the original request.
                 */
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
