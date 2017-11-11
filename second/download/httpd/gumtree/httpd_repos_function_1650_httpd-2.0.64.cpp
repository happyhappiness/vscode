int cache_select_url(request_rec *r, char *url)
{
    cache_provider_list *list;
    apr_status_t rv;
    cache_handle_t *h;
    char *key;
    cache_request_rec *cache = (cache_request_rec *) 
                         ap_get_module_config(r->request_config, &cache_module);

    rv = cache_generate_key(r, r->pool, &key);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    /* go through the cache types till we get a match */
    h = apr_palloc(r->pool, sizeof(cache_handle_t));

    list = cache->providers;

    while (list) {
        switch ((rv = list->provider->open_entity(h, r, key))) {
        case OK: {
            char *vary = NULL;
            const char *varyhdr = NULL;
            int fresh;

            if (list->provider->recall_headers(h, r) != APR_SUCCESS) {
                /* TODO: Handle this error */
                return DECLINED;
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
            if ((varyhdr = apr_table_get(h->resp_err_hdrs, "Vary")) == NULL) {
                varyhdr = apr_table_get(h->resp_hdrs, "Vary");
            }
            vary = apr_pstrdup(r->pool, varyhdr);
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
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                r->server,
                                "cache_select_url(): Vary header mismatch.");
                    return DECLINED;
                }
            }

            cache->provider = list->provider;
            cache->provider_name = list->provider_name;

            /* Is our cached response fresh enough? */
            fresh = ap_cache_check_freshness(h, r);
            if (!fresh) {
                cache_info *info = &(h->cache_obj->info);

                /* Make response into a conditional */
                /* FIXME: What if the request is already conditional? */
                if (info && info->etag) {
                    /* if we have a cached etag */
                    cache->stale_headers = apr_table_copy(r->pool,
                                                          r->headers_in);
                    apr_table_set(r->headers_in, "If-None-Match", info->etag);
                    cache->stale_handle = h;
                }
                else if (info && info->lastmods) {
                    /* if we have a cached Last-Modified header */
                    cache->stale_headers = apr_table_copy(r->pool,
                                                          r->headers_in);
                    apr_table_set(r->headers_in, "If-Modified-Since",
                                  info->lastmods);
                    cache->stale_handle = h;
                }

                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            apr_table_setn(r->headers_out, "Content-Type",
                           ap_make_content_type(r, h->content_type));
            r->filename = apr_pstrdup(r->pool, h->cache_obj->info.filename);
            accept_headers(h, r);

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
    return DECLINED;
}