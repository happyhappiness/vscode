    cache->handle = apr_palloc(r->pool, sizeof(cache_handle_t));

    while (next) {
        type = ap_cache_tokstr(r->pool, next, &next);
        switch ((rv = cache_run_open_entity(cache->handle, r, type, key))) {
        case OK: {
            char *vary = NULL;
            info = &(cache->handle->cache_obj->info);
            if (cache_read_entity_headers(cache->handle, r) != APR_SUCCESS) {
                /* TODO: Handle this error */
                return DECLINED;
            }

            /*
             * Check Content-Negotiation - Vary
             * 
             * At this point we need to make sure that the object we found in the cache
             * is the same object that would be delivered to the client, when the
             * effects of content negotiation are taken into effect.
             * 
             * In plain english, we want to make sure that a language-negotiated
             * document in one language is not given to a client asking for a
             * language negotiated document in a different language by mistake.
             * 
             * This code makes the assumption that the storage manager will
             * cache the info->req_hdrs if the response contains a Vary
             * header.
             * 
             * RFC2616 13.6 and 14.44 describe the Vary mechanism.
             */
            vary = ap_pstrdup(r->pool, ap_table_get(r->headers_out, "Vary"));
            while (vary && *vary) {
                char *name = vary;
                const char *h1, *h2;

                /* isolate header name */
                while (*vary && !ap_isspace(*vary) && (*vary != ','))
                    ++vary;
                while (*vary && (ap_isspace(*vary) || (*vary == ','))) {
                    *vary = '\0';
                    ++vary;
                }

                /*
                 * is this header in the request and the header in the cached
                 * request identical? If not, we give up and do a straight get
                 */
                h1 = ap_table_get(r->headers_in, name);
                h2 = ap_table_get(info->req_hdrs, name);
                if (h1 == h2) {
                    /* both headers NULL, so a match - do nothing */
                }
                else if (h1 && h2 && !strcmp(h1, h2)) {
                    /* both headers exist and are equal - do nothing */
                }
                else {
                    /* headers do not match, so Vary failed */
                    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r->server,
                                 "cache_select_url(): Vary header mismatch - Cached document cannot be used. \n");
                    apr_table_clear(r->headers_out);
                    r->status_line = NULL;
                    cache->handle = NULL;
                    return DECLINED;
                }
            }
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
            continue;
        }
