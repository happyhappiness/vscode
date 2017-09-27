     if (conf->ignorecachecontrol == 1 && auth == NULL) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "incoming request is asking for a uncached version of "
                      "%s, but we know better and are ignoring it", url);
     }
     else {
-        if (ap_cache_liststr(NULL, cc_in, "no-store", NULL) ||
-            ap_cache_liststr(NULL, pragma, "no-cache", NULL) || (auth != NULL)) {
-            /* delete the previously cached file */
-            cache_remove_url(r, cache->types, url);
-
+        if (ap_cache_liststr(NULL, pragma, "no-cache", NULL) ||
+            auth != NULL) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                         "cache: no-store forbids caching of %s", url);
+                         "cache: no-cache or authorization forbids caching "
+                         "of %s", url);
             return DECLINED;
         }
     }
 
     /*
      * Try to serve this request from the cache.
      *
-     * If no existing cache file
-     *   add cache_in filter
-     * If stale cache file
-     *   If conditional request
-     *     add cache_in filter
-     *   If non-conditional request
-     *     fudge response into a conditional
-     *     add cache_conditional filter
-     * If fresh cache file
-     *   clear filter stack
-     *   add cache_out filter
-     */
-
-    rv = cache_select_url(r, cache->types, url);
-    if (DECLINED == rv) {
-        if (!lookup) {
-            /* no existing cache file */
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                         "cache: no cache - add cache_in filter and DECLINE");
-            /* add cache_in filter to cache this request */
-            ap_add_output_filter_handle(cache_in_filter_handle, NULL, r,
-                                        r->connection);
+     * If no existing cache file (DECLINED)
+     *   add cache_save filter
+     * If cached file (OK)
+     *   If fresh cache file
+     *     clear filter stack
+     *     add cache_out filter
+     *     return OK
+     *   If stale cache file
+     *       add cache_conditional filter (which updates cache)
+     */
+
+    rv = cache_select_url(r, url);
+    if (rv != OK) {
+        if (rv == DECLINED) {
+            if (!lookup) {
+                /* add cache_save filter to cache this request */
+                ap_add_output_filter_handle(cache_save_filter_handle, NULL, r,
+                                            r->connection);
+            }
+        }
+        else {
+            /* error */
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+                         "cache: error returned while checking for cached "
+                         "file by %s cache", cache->provider_name);
         }
         return DECLINED;
     }
-    else if (OK == rv) {
-        /* RFC2616 13.2 - Check cache object expiration */
-        cache->fresh = ap_cache_check_freshness(cache, r);
-        if (cache->fresh) {
-            /* fresh data available */
-            apr_bucket_brigade *out;
-            conn_rec *c = r->connection;
 
-            if (lookup) {
-                return OK;
-            }
-            rv = ap_meets_conditions(r);
-            if (rv != OK) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                             "cache: fresh cache - returning status %d", rv);
-                return rv;
-            }
+    /* We have located a suitable cache file now. */
 
-            /*
-             * Not a conditionl request. Serve up the content 
-             */
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                         "cache: fresh cache - add cache_out filter and "
-                         "handle request");
+    /* RFC2616 13.2 - Check cache object expiration */
+    cache->fresh = ap_cache_check_freshness(cache, r);
 
-            /* We are in the quick handler hook, which means that no output
-             * filters have been set. So lets run the insert_filter hook.
-             */
-            ap_run_insert_filter(r);
-            ap_add_output_filter_handle(cache_out_filter_handle, NULL,
-                                        r, r->connection);
-
-            /* kick off the filter stack */
-            out = apr_brigade_create(r->pool, c->bucket_alloc);
-            if (APR_SUCCESS
-                != (rv = ap_pass_brigade(r->output_filters, out))) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                             "cache: error returned while trying to return %s "
-                             "cached data", 
-                             cache->type);
-                return rv;
-            }
-            return OK;
-        }
-        else {
-            if (!r->err_headers_out) {
-                r->err_headers_out = apr_table_make(r->pool, 3);
+    /* What we have in our cache isn't fresh. */
+    if (!cache->fresh) {
+        /* If our stale cached response was conditional... */
+        if (!lookup && ap_cache_request_is_conditional(r)) {
+            info = &(cache->handle->cache_obj->info);
+
+            /* fudge response into a conditional */
+            if (info && info->etag) {
+                /* if we have a cached etag */
+                apr_table_set(r->headers_in, "If-None-Match", info->etag);
             }
-            /* stale data available */
-            if (lookup) {
-                return DECLINED;
+            else if (info && info->lastmods) {
+                /* if we have a cached IMS */
+                apr_table_set(r->headers_in, "If-Modified-Since",
+                              info->lastmods);
             }
+        }
 
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                         "cache: stale cache - test conditional");
-            /* if conditional request */
-            if (ap_cache_request_is_conditional(r)) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
-                             r->server,
-                             "cache: conditional - add cache_in filter and "
-                             "DECLINE");
-                /* Why not add CACHE_CONDITIONAL? */
-                ap_add_output_filter_handle(cache_in_filter_handle, NULL,
-                                            r, r->connection);
+        /* Add cache_conditional_filter to see if we can salvage
+         * later.
+         */
+        ap_add_output_filter_handle(cache_conditional_filter_handle,
+                                    NULL, r, r->connection);
+        return DECLINED;
+    }
 
-                return DECLINED;
-            }
-            /* else if non-conditional request */
-            else {
-                /* Temporarily hack this to work the way it had been. Its broken,
-                 * but its broken the way it was before. I'm working on figuring
-                 * out why the filter add in the conditional filter doesn't work. pjr
-                 *
-                 * info = &(cache->handle->cache_obj->info);
-                 *
-                 * Uncomment the above when the code in cache_conditional_filter_handle
-                 * is properly fixed...  pjr
-                 */
-                
-                /* fudge response into a conditional */
-                if (info && info->etag) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
-                                 r->server,
-                                 "cache: nonconditional - fudge conditional "
-                                 "by etag");
-                    /* if we have a cached etag */
-                    apr_table_set(r->headers_in, "If-None-Match", info->etag);
-                }
-                else if (info && info->lastmods) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
-                                 r->server,
-                                 "cache: nonconditional - fudge conditional "
-                                 "by lastmod");
-                    /* if we have a cached IMS */
-                    apr_table_set(r->headers_in, 
-                                  "If-Modified-Since", 
-                                  info->lastmods);
-                }
-                else {
-                    /* something else - pretend there was no cache */
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
-                                 r->server,
-                                 "cache: nonconditional - no cached "
-                                 "etag/lastmods - add cache_in and DECLINE");
-
-                    ap_add_output_filter_handle(cache_in_filter_handle, NULL,
-                                                r, r->connection);
-
-                    return DECLINED;
-                }
-                /* add cache_conditional filter */
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
-                             r->server,
-                             "cache: nonconditional - add cache_conditional "
-                             "and DECLINE");
-                ap_add_output_filter_handle(cache_conditional_filter_handle,
-                                            NULL, 
-                                            r, 
-                                            r->connection);
+    /* fresh data available */
 
-                return DECLINED;
-            }
-        }
+    info = &(cache->handle->cache_obj->info);
+
+    if (info && info->lastmod) {
+        ap_update_mtime(r, info->lastmod);
     }
-    else {
-        /* error */
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, 
-                     r->server,
-                     "cache: error returned while checking for cached file by "
-                     "%s cache", 
-                     cache->type);
-        return DECLINED;
+
+    rv = ap_meets_conditions(r);
+    if (rv != OK) {
+        /* Return cached status. */
+        return rv;
+    }
+
+    /* If we're a lookup, we can exit now instead of serving the content. */
+    if (lookup) {
+        return OK;
     }
+
+    /* Serve up the content */
+
+    /* We are in the quick handler hook, which means that no output
+     * filters have been set. So lets run the insert_filter hook.
+     */
+    ap_run_insert_filter(r);
+    ap_add_output_filter_handle(cache_out_filter_handle, NULL,
+                                r, r->connection);
+
+    /* kick off the filter stack */
+    out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+    rv = ap_pass_brigade(r->output_filters, out);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+                     "cache: error returned while trying to return %s "
+                     "cached data", 
+                     cache->provider_name);
+        return rv;
+    }
+
+    return OK;
 }
 
 /*
  * CACHE_OUT filter
  * ----------------
  *
