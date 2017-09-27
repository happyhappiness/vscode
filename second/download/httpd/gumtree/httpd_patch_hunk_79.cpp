  */
 
 static int cache_in_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     int rv;
     request_rec *r = f->r;
+    cache_request_rec *cache;
+    cache_server_conf *conf;
     char *url = r->unparsed_uri;
-    const char *cc_out = apr_table_get(r->headers_out, "Cache-Control");
+    const char *cc_out, *cl;
     const char *exps, *lastmods, *dates, *etag;
     apr_time_t exp, date, lastmod, now;
     apr_off_t size;
     cache_info *info;
-    void *sconf = r->server->module_config;
-    cache_server_conf *conf =
-        (cache_server_conf *) ap_get_module_config(sconf, &cache_module);
-    void *scache = r->request_config;
-    cache_request_rec *cache =
-        (cache_request_rec *) ap_get_module_config(scache, &cache_module);
-    apr_bucket *split_point = NULL;
-
-
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
-                 "cache: running CACHE_IN filter");
+    char *reason;
+    apr_pool_t *p;
 
     /* check first whether running this filter has any point or not */
     if(r->no_cache) {
         ap_remove_output_filter(f);
         return ap_pass_brigade(f->next, in);
     }
 
-    /* make space for the per request config 
-     * We hit this code path when CACHE_IN has been installed by someone
-     * other than the cache handler
-     */
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                 "cache: running CACHE_IN filter");
+
+    /* Setup cache_request_rec */
+    cache = (cache_request_rec *) ap_get_module_config(r->request_config, &cache_module);
     if (!cache) {
         cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
         ap_set_module_config(r->request_config, &cache_module, cache);
     }
 
-    /* If we've previously processed and set aside part of this
-     * response, skip the cacheability checks
+    reason = NULL;
+    p = r->pool;
+    /*
+     * Pass Data to Cache
+     * ------------------
+     * This section passes the brigades into the cache modules, but only
+     * if the setup section (see below) is complete.
      */
-    if (cache->saved_brigade != NULL) {
-        exp = cache->exp;
-        lastmod = cache->lastmod;
-        info = cache->info;
-    }
-    else {
 
-        /*
-         * Pass Data to Cache
-         * ------------------
-         * This section passes the brigades into the cache modules, but only
-         * if the setup section (see below) is complete.
+    /* have we already run the cachability check and set up the
+     * cached file handle? 
+     */
+    if (cache->in_checked) {
+        /* pass the brigades into the cache, then pass them
+         * up the filter stack
          */
-
-        /* have we already run the cachability check and set up the
-         * cached file handle? 
-         */
-        if (cache->in_checked) {
-            /* pass the brigades into the cache, then pass them
-             * up the filter stack
-             */
-            rv = cache_write_entity_body(cache->handle, r, in);
-            if (rv != APR_SUCCESS) {
-                ap_remove_output_filter(f);
-            }
-            return ap_pass_brigade(f->next, in);
+        rv = cache_write_entity_body(cache->handle, r, in);
+        if (rv != APR_SUCCESS) {
+            ap_remove_output_filter(f);
         }
+        return ap_pass_brigade(f->next, in);
+    }
 
-        /*
-         * Setup Data in Cache
-         * -------------------
-         * This section opens the cache entity and sets various caching
-         * parameters, and decides whether this URL should be cached at
-         * all. This section is* run before the above section.
-         */
-        info = apr_pcalloc(r->pool, sizeof(cache_info));
-
-        /* read expiry date; if a bad date, then leave it so the client can
-         * read it 
-         */
-        exps = apr_table_get(r->headers_out, "Expires");
-        if (exps != NULL) {
-            if (APR_DATE_BAD == (exp = apr_date_parse_http(exps))) {
-                exps = NULL;
-            }
-        }
-        else {
-            exp = APR_DATE_BAD;
+    /*
+     * Setup Data in Cache
+     * -------------------
+     * This section opens the cache entity and sets various caching
+     * parameters, and decides whether this URL should be cached at
+     * all. This section is* run before the above section.
+     */
+    info = apr_pcalloc(r->pool, sizeof(cache_info));
+
+    /* read expiry date; if a bad date, then leave it so the client can
+     * read it 
+     */
+    exps = apr_table_get(r->headers_out, "Expires");
+    if (exps != NULL) {
+        if (APR_DATE_BAD == (exp = apr_date_parse_http(exps))) {
+            exps = NULL;
         }
+    }
+    else {
+        exp = APR_DATE_BAD;
+    }
 
-        /* read the last-modified date; if the date is bad, then delete it */
-        lastmods = apr_table_get(r->headers_out, "Last-Modified");
-        if (lastmods != NULL) {
-            if (APR_DATE_BAD == (lastmod = apr_date_parse_http(lastmods))) {
-                lastmods = NULL;
-            }
+    /* read the last-modified date; if the date is bad, then delete it */
+    lastmods = apr_table_get(r->headers_out, "Last-Modified");
+    if (lastmods != NULL) {
+        if (APR_DATE_BAD == (lastmod = apr_date_parse_http(lastmods))) {
+            lastmods = NULL;
         }
-        else {
-            lastmod = APR_DATE_BAD;
-        }
-
-        /* read the etag from the entity */
-        etag = apr_table_get(r->headers_out, "Etag");
+    }
+    else {
+        lastmod = APR_DATE_BAD;
+    }
 
-        /*
-         * what responses should we not cache?
-         *
-         * At this point we decide based on the response headers whether it
-         * is appropriate _NOT_ to cache the data from the server. There are
-         * a whole lot of conditions that prevent us from caching this data.
-         * They are tested here one by one to be clear and unambiguous. 
-         */
+    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config, &cache_module);
+    /* read the etag and cache-control from the entity */
+    etag = apr_table_get(r->headers_out, "Etag");
+    cc_out = apr_table_get(r->headers_out, "Cache-Control");
 
+    /*
+     * what responses should we not cache?
+     *
+     * At this point we decide based on the response headers whether it
+     * is appropriate _NOT_ to cache the data from the server. There are
+     * a whole lot of conditions that prevent us from caching this data.
+     * They are tested here one by one to be clear and unambiguous. 
+     */
+    if (r->status != HTTP_OK && r->status != HTTP_NON_AUTHORITATIVE
+        && r->status != HTTP_MULTIPLE_CHOICES
+        && r->status != HTTP_MOVED_PERMANENTLY
+        && r->status != HTTP_NOT_MODIFIED) {
         /* RFC2616 13.4 we are allowed to cache 200, 203, 206, 300, 301 or 410
          * We don't cache 206, because we don't (yet) cache partial responses.
          * We include 304 Not Modified here too as this is the origin server
          * telling us to serve the cached copy.
          */
-        if ((r->status != HTTP_OK && r->status != HTTP_NON_AUTHORITATIVE
-             && r->status != HTTP_MULTIPLE_CHOICES
-             && r->status != HTTP_MOVED_PERMANENTLY
-             && r->status != HTTP_NOT_MODIFIED)
-            /* if a broken Expires header is present, don't cache it */
-            || (exps != NULL && exp == APR_DATE_BAD)
-            /* if query string present but no expiration time, don't cache it
-             * (RFC 2616/13.9)
-             */
-            || (r->args && exps == NULL)
-            /* if the server said 304 Not Modified but we have no cache
-             * file - pass this untouched to the user agent, it's not for us.
-             */
-            || (r->status == HTTP_NOT_MODIFIED && (NULL == cache->handle))
-            /* 200 OK response from HTTP/1.0 and up without a Last-Modified
-             * header/Etag 
-             */
-            /* XXX mod-include clears last_modified/expires/etags - this
-             * is why we have an optional function for a key-gen ;-) 
-             */
-            || (r->status == HTTP_OK && lastmods == NULL && etag == NULL 
-                && (conf->no_last_mod_ignore ==0))
-            /* HEAD requests */
-            || r->header_only
-            /* RFC2616 14.9.2 Cache-Control: no-store response
-             * indicating do not cache, or stop now if you are
-             * trying to cache it */
-            || ap_cache_liststr(cc_out, "no-store", NULL)
-            /* RFC2616 14.9.1 Cache-Control: private
-             * this object is marked for this user's eyes only. Behave
-             * as a tunnel.
-             */
-            || ap_cache_liststr(cc_out, "private", NULL)
-            /* RFC2616 14.8 Authorisation:
-             * if authorisation is included in the request, we don't cache,
-             * but we can cache if the following exceptions are true:
-             * 1) If Cache-Control: s-maxage is included
-             * 2) If Cache-Control: must-revalidate is included
-             * 3) If Cache-Control: public is included
-             */
-            || (apr_table_get(r->headers_in, "Authorization") != NULL
-                && !(ap_cache_liststr(cc_out, "s-maxage", NULL)
-                     || ap_cache_liststr(cc_out, "must-revalidate", NULL)
-                     || ap_cache_liststr(cc_out, "public", NULL)))
-            /* or we've been asked not to cache it above */
-            || r->no_cache) {
-
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                         "cache: response is not cachable");
-
-            /* remove this object from the cache 
-             * BillS Asks.. Why do we need to make this call to remove_url?
-             * leave it in for now..
-             */
-            cache_remove_url(r, cache->types, url);
-
-            /* remove this filter from the chain */
-            ap_remove_output_filter(f);
-
-            /* ship the data up the stack */
-            return ap_pass_brigade(f->next, in);
-        }
-        cache->in_checked = 1;
-    } /* if cache->saved_brigade==NULL */
-
-    /* Set the content length if known.  We almost certainly do NOT want to
-     * cache streams with unknown content lengths in the in-memory cache.
-     * Streams with unknown content length should be first cached in the
-     * file system. If they are withing acceptable limits, then they can be 
-     * moved to the in-memory cache.
-     */
-    {
-        const char* cl;
-        cl = apr_table_get(r->headers_out, "Content-Length");
-        if (cl) {
-            size = apr_atoi64(cl);
-        }
-        else {
+        reason = apr_psprintf(p, "Response status %d", r->status);
+    } 
+    else if (exps != NULL && exp == APR_DATE_BAD) {
+        /* if a broken Expires header is present, don't cache it */
+        reason = apr_pstrcat(p, "Broken expires header: ", exps, NULL);
+    }
+    else if (r->args && exps == NULL) {
+        /* if query string present but no expiration time, don't cache it
+         * (RFC 2616/13.9)
+         */
+        reason = "Query string present but no expires header";
+    }
+    else if (r->status == HTTP_NOT_MODIFIED && (NULL == cache->handle)) {
+        /* if the server said 304 Not Modified but we have no cache
+         * file - pass this untouched to the user agent, it's not for us.
+         */
+        reason = "HTTP Status 304 Not Modified";
+    }
+    else if (r->status == HTTP_OK && lastmods == NULL && etag == NULL 
+             && (conf->no_last_mod_ignore ==0)) {
+        /* 200 OK response from HTTP/1.0 and up without a Last-Modified
+         * header/Etag 
+         */
+        /* XXX mod-include clears last_modified/expires/etags - this
+         * is why we have an optional function for a key-gen ;-) 
+         */
+        reason = "No Last-Modified or Etag header";
+    }
+    else if (r->header_only) {
+        /* HEAD requests */
+        reason = "HTTP HEAD request";
+    }
+    else if (ap_cache_liststr(NULL, cc_out, "no-store", NULL)) {
+        /* RFC2616 14.9.2 Cache-Control: no-store response
+         * indicating do not cache, or stop now if you are
+         * trying to cache it */
+        reason = "Cache-Control: no-store present";
+    }
+    else if (ap_cache_liststr(NULL, cc_out, "private", NULL)) {
+        /* RFC2616 14.9.1 Cache-Control: private
+         * this object is marked for this user's eyes only. Behave
+         * as a tunnel.
+         */
+        reason = "Cache-Control: private present";
+    }
+    else if (apr_table_get(r->headers_in, "Authorization") != NULL
+             && !(ap_cache_liststr(NULL, cc_out, "s-maxage", NULL)
+                  || ap_cache_liststr(NULL, cc_out, "must-revalidate", NULL)
+                  || ap_cache_liststr(NULL, cc_out, "public", NULL))) {
+        /* RFC2616 14.8 Authorisation:
+         * if authorisation is included in the request, we don't cache,
+         * but we can cache if the following exceptions are true:
+         * 1) If Cache-Control: s-maxage is included
+         * 2) If Cache-Control: must-revalidate is included
+         * 3) If Cache-Control: public is included
+         */
+        reason = "Authorization required";
+    }
+    else if (r->no_cache) {
+        /* or we've been asked not to cache it above */
+        reason = "no_cache present";
+    }
 
-            /* if we don't get the content-length, see if we have all the 
-             * buckets and use their length to calculate the size 
-             */
-            apr_bucket *e;
-            int all_buckets_here=0;
-            int unresolved_length = 0;
-            size=0;
-            APR_BRIGADE_FOREACH(e, in) {
-                if (APR_BUCKET_IS_EOS(e)) {
-                    all_buckets_here=1;
-                    break;
-                }
-                if (APR_BUCKET_IS_FLUSH(e)) {
-                    unresolved_length = 1;
-                    continue;
-                }
-                if (e->length < 0) {
-                    break;
-                }
-                size += e->length;
-            }
+    if (reason) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "cache: %s not cached. Reason: %s", url, reason);
+        /* remove this object from the cache 
+         * BillS Asks.. Why do we need to make this call to remove_url?
+         * leave it in for now..
+         */
+        cache_remove_url(r, cache->types, url);
 
-            if (!all_buckets_here) {
-                /* Attempt to set aside a copy of a partial response
-                 * in hopes of caching it once the rest of the response
-                 * is available.  There are special cases in which we
-                 * don't try to set aside the content, though:
-                 *   1. The brigade contains at least one bucket of
-                 *      unknown length, such as a pipe or socket bucket.
-                 *   2. The size of the response exceeds the limit set
-                 *      by the CacheMaxStreamingBuffer  directive.
-                 */
-                if (unresolved_length ||
-                    (cache->saved_size + size >
-                     conf->max_streaming_buffer_size)) {
-
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                                 "cache: not caching streamed response for "
-                                 "%s because length %s", url,
-                                 (unresolved_length ?
-                                  "cannot be determined" :
-                                  "> CacheMaxStreamingBuffer"));
-
-                    if (cache->saved_brigade != NULL) {
-                        apr_brigade_destroy(cache->saved_brigade);
-                        cache->saved_brigade = NULL;
-                        cache->saved_size = 0;
-                    }
-                    ap_remove_output_filter(f);
-                    return ap_pass_brigade(f->next, in);
-                }
+        /* remove this filter from the chain */
+        ap_remove_output_filter(f);
 
-                /* Add a copy of the new brigade's buckets to the
-                 * saved brigade.  The reason for the copy is so
-                 * that we can output the new buckets immediately,
-                 * rather than having to buffer up the entire
-                 * response before sending anything.
-                 */
-                if (cache->saved_brigade == NULL) {
-                    cache->saved_brigade =
-                        apr_brigade_create(r->pool,
-                                           r->connection->bucket_alloc);
-                    cache->exp = exp;
-                    cache->lastmod = lastmod;
-                    cache->info = info;
-                }
-                APR_BRIGADE_FOREACH(e, in) {
-                    apr_bucket *copy;
-                    rv = apr_bucket_copy(e, &copy);
-                    if (rv == APR_ENOTIMPL) {
-                        const char *str;
-                        apr_size_t len;
-
-                        /* This takes care of uncopyable buckets. */
-                        rv = apr_bucket_read(e, &str, &len, APR_BLOCK_READ);
-                        if ((rv == APR_SUCCESS) &&
-                            (cache->saved_size + len <=
-                                        conf->max_streaming_buffer_size)) {
-                            rv = apr_bucket_copy(e, &copy);
-                        }
-
-                        if ((rv != APR_SUCCESS) ||
-                            (cache->saved_size + len >
-                                        conf->max_streaming_buffer_size)){
-                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                                         "cache: not caching streamed response for "
-                                         "%s because length %s", url,
-                                          "> CacheMaxStreamingBuffer");
-
-                            if (cache->saved_brigade != NULL) {
-                                apr_brigade_destroy(cache->saved_brigade);
-                                cache->saved_brigade = NULL;
-                                cache->saved_size = 0;
-                            }
-                            ap_remove_output_filter(f);
-                            return ap_pass_brigade(f->next, in);
-                        }
-                    }
-                    APR_BRIGADE_INSERT_TAIL(cache->saved_brigade, copy);
-                }
-                cache->saved_size += size;
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                             "cache: Response length still unknown, setting "
-                             "aside content for url: %s", url);
+        /* ship the data up the stack */
+        return ap_pass_brigade(f->next, in);
+    }
+    cache->in_checked = 1;
 
-                return ap_pass_brigade(f->next, in);
+    /* Set the content length if known. 
+     */
+    cl = apr_table_get(r->headers_out, "Content-Length");
+    if (cl) {
+        size = apr_atoi64(cl);
+    }
+    else {
+        /* if we don't get the content-length, see if we have all the 
+         * buckets and use their length to calculate the size 
+         */
+        apr_bucket *e;
+        int all_buckets_here=0;
+        int unresolved_length = 0;
+        size=0;
+        APR_BRIGADE_FOREACH(e, in) {
+            if (APR_BUCKET_IS_EOS(e)) {
+                all_buckets_here=1;
+                break;
+            }
+            if (APR_BUCKET_IS_FLUSH(e)) {
+                unresolved_length = 1;
+                continue;
             }
-            else {
-                /* Now that we've seen an EOS, it's appropriate
-                 * to try caching the response.  If any content
-                 * has been copied into cache->saved_brigade in
-                 * previous passes through this filter, the
-                 * content placed in the cache must be the
-                 * concatenation of the saved brigade and the
-                 * current brigade.
-                 */
-                if (cache->saved_brigade != NULL) {
-                    split_point = APR_BRIGADE_FIRST(in);
-                    APR_BRIGADE_CONCAT(cache->saved_brigade, in);
-                    in = cache->saved_brigade;
-                    size += cache->saved_size;
-                }
+            if (e->length == (apr_size_t)-1) {
+                break;
             }
+            size += e->length;
+        }
+        if (!all_buckets_here) {
+            size = -1;
         }
     }
 
     /* It's safe to cache the response.
      *
      * There are two possiblities at this point:
