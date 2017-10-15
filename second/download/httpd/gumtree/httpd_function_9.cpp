static int cache_in_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    int rv;
    request_rec *r = f->r;
    char *url = r->unparsed_uri;
    const char *cc_out = apr_table_get(r->headers_out, "Cache-Control");
    const char *exps, *lastmods, *dates, *etag;
    apr_time_t exp, date, lastmod, now;
    apr_off_t size;
    cache_info *info;
    void *sconf = r->server->module_config;
    cache_server_conf *conf =
        (cache_server_conf *) ap_get_module_config(sconf, &cache_module);
    void *scache = r->request_config;
    cache_request_rec *cache =
        (cache_request_rec *) ap_get_module_config(scache, &cache_module);
    apr_bucket *split_point = NULL;


    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "cache: running CACHE_IN filter");

    /* check first whether running this filter has any point or not */
    if(r->no_cache) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, in);
    }

    /* make space for the per request config 
     * We hit this code path when CACHE_IN has been installed by someone
     * other than the cache handler
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
     */
    {
        const char* cl;
        cl = apr_table_get(r->headers_out, "Content-Length");
        if (cl) {
            size = apr_atoi64(cl);
        }
        else {

            /* if we don't get the content-length, see if we have all the 
             * buckets and use their length to calculate the size 
             */
            apr_bucket *e;
            int all_buckets_here=0;
            int unresolved_length = 0;
            size=0;
            APR_BRIGADE_FOREACH(e, in) {
                if (APR_BUCKET_IS_EOS(e)) {
                    all_buckets_here=1;
                    break;
                }
                if (APR_BUCKET_IS_FLUSH(e)) {
                    unresolved_length = 1;
                    continue;
                }
                if (e->length < 0) {
                    break;
                }
                size += e->length;
            }

            if (!all_buckets_here) {
                /* Attempt to set aside a copy of a partial response
                 * in hopes of caching it once the rest of the response
                 * is available.  There are special cases in which we
                 * don't try to set aside the content, though:
                 *   1. The brigade contains at least one bucket of
                 *      unknown length, such as a pipe or socket bucket.
                 *   2. The size of the response exceeds the limit set
                 *      by the CacheMaxStreamingBuffer  directive.
                 */
                if (unresolved_length ||
                    (cache->saved_size + size >
                     conf->max_streaming_buffer_size)) {

                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "cache: not caching streamed response for "
                                 "%s because length %s", url,
                                 (unresolved_length ?
                                  "cannot be determined" :
                                  "> CacheMaxStreamingBuffer"));

                    if (cache->saved_brigade != NULL) {
                        apr_brigade_destroy(cache->saved_brigade);
                        cache->saved_brigade = NULL;
                        cache->saved_size = 0;
                    }
                    ap_remove_output_filter(f);
                    return ap_pass_brigade(f->next, in);
                }

                /* Add a copy of the new brigade's buckets to the
                 * saved brigade.  The reason for the copy is so
                 * that we can output the new buckets immediately,
                 * rather than having to buffer up the entire
                 * response before sending anything.
                 */
                if (cache->saved_brigade == NULL) {
                    cache->saved_brigade =
                        apr_brigade_create(r->pool,
                                           r->connection->bucket_alloc);
                    cache->exp = exp;
                    cache->lastmod = lastmod;
                    cache->info = info;
                }
                APR_BRIGADE_FOREACH(e, in) {
                    apr_bucket *copy;
                    apr_bucket_copy(e, &copy);
                    APR_BRIGADE_INSERT_TAIL(cache->saved_brigade, copy);
                }
                cache->saved_size += size;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "cache: Response length still unknown, setting "
                             "aside content for url: %s", url);

                return ap_pass_brigade(f->next, in);
            }
            else {
                /* Now that we've seen an EOS, it's appropriate
                 * to try caching the response.  If any content
                 * has been copied into cache->saved_brigade in
                 * previous passes through this filter, the
                 * content placed in the cache must be the
                 * concatenation of the saved brigade and the
                 * current brigade.
                 */
                if (cache->saved_brigade != NULL) {
                    split_point = APR_BRIGADE_FIRST(in);
                    APR_BRIGADE_CONCAT(cache->saved_brigade, in);
                    in = cache->saved_brigade;
                    size += cache->saved_size;
                }
            }
        }
    }

    /* It's safe to cache the response.
     *
     * There are two possiblities at this point:
     * - cache->handle == NULL. In this case there is no previously
     * cached entity anywhere on the system. We must create a brand
     * new entity and store the response in it.
     * - cache->handle != NULL. In this case there is a stale
     * entity in the system which needs to be replaced by new
     * content (unless the result was 304 Not Modified, which means
     * the cached entity is actually fresh, and we should update
     * the headers).
     */
    /* no cache handle, create a new entity */
    if (!cache->handle) {
        rv = cache_create_entity(r, cache->types, url, size);
    }
    /* pre-existing cache handle and 304, make entity fresh */
    else if (r->status == HTTP_NOT_MODIFIED) {
        /* update headers */

        /* remove this filter ??? */

        /* XXX is this right?  we must set rv to something other than OK 
         * in this path
         */
        rv = HTTP_NOT_MODIFIED;
    }
    /* pre-existing cache handle and new entity, replace entity
     * with this one
     */
    else {
        cache_remove_entity(r, cache->types, cache->handle);
        rv = cache_create_entity(r, cache->types, url, size);
    }
    
    if (rv != OK) {
        /* Caching layer declined the opportunity to cache the response */
        ap_remove_output_filter(f);
        if (split_point) {
            apr_bucket_brigade *already_sent = in;
            in = apr_brigade_split(in, split_point);
            apr_brigade_destroy(already_sent);
        }
        return ap_pass_brigade(f->next, in);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "cache: Caching url: %s", url);

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
    dates = apr_table_get(r->headers_out, "Date");
    if (dates != NULL) {
        info->date = apr_date_parse_http(dates);
    }
    else {
        info->date = APR_DATE_BAD;
    }

    now = apr_time_now();
    if (info->date == APR_DATE_BAD) {  /* No, or bad date */
        char *dates;
        /* no date header! */
        /* add one; N.B. use the time _now_ rather than when we were checking
         * the cache 
         */
        date = now;
        dates = apr_pcalloc(r->pool, MAX_STRING_LEN);
        apr_rfc822_date(dates, now);
        apr_table_set(r->headers_out, "Date", dates);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: Added date header");
        info->date = date;
    }
    else {
        date = info->date;
    }

    /* set response_time for HTTP/1.1 age calculations */
    info->response_time = now;

    /* get the request time */
    info->request_time = r->request_time;

    /* check last-modified date */
    /* XXX FIXME we're referencing date on a path where we didn't set it */
    if (lastmod != APR_DATE_BAD && lastmod > date) {
        /* if it's in the future, then replace by date */
        lastmod = date;
        lastmods = dates;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                     r->server,
                     "cache: Last modified is in the future, "
                     "replacing with now");
    }
    info->lastmod = lastmod;

    /* if no expiry date then
     *   if lastmod
     *      expiry date = now + min((date - lastmod) * factor, maxexpire)
     *   else
     *      expire date = now + defaultexpire
     */
    if (exp == APR_DATE_BAD) {
        if (lastmod != APR_DATE_BAD) {
            apr_time_t x = (apr_time_t) ((date - lastmod) * conf->factor);
            if (x > conf->maxex) {
                x = conf->maxex;
            }
            exp = now + x;
        }
        else {
            exp = now + conf->defex;
        }
    }
    info->expire = exp;

    info->content_type = apr_pstrdup(r->pool, r->content_type);
    info->filename = apr_pstrdup(r->pool, r->filename );

    /*
     * Write away header information to cache.
     */
    rv = cache_write_entity_headers(cache->handle, r, info);
    if (rv == APR_SUCCESS) {
        rv = cache_write_entity_body(cache->handle, r, in);
    }
    if (rv != APR_SUCCESS) {
        ap_remove_output_filter(f);
    }
    if (split_point) {
        apr_bucket_brigade *already_sent = in;
        in = apr_brigade_split(in, split_point);
        apr_brigade_destroy(already_sent);
    }
    return ap_pass_brigade(f->next, in);
}