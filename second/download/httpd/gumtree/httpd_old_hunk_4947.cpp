             * This code makes the assumption that the storage manager will
             * cache the req_hdrs if the response contains a Vary
             * header.
             *
             * RFC2616 13.6 and 14.44 describe the Vary mechanism.
             */
            vary = apr_pstrdup(r->pool, apr_table_get(h->resp_hdrs, "Vary"));
            while (vary && *vary) {
                char *name = vary;
                const char *h1, *h2;

                /* isolate header name */
                while (*vary && !apr_isspace(*vary) && (*vary != ','))
                    ++vary;
                while (*vary && (apr_isspace(*vary) || (*vary == ','))) {
                    *vary = '\0';
                    ++vary;
                }

                /*
                 * is this header in the request and the header in the cached
                 * request identical? If not, we give up and do a straight get
                 */
                h1 = apr_table_get(r->headers_in, name);
                h2 = apr_table_get(h->req_hdrs, name);
                if (h1 == h2) {
                    /* both headers NULL, so a match - do nothing */
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
