 
         lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
     }
     return apr_file_remove(lockname, r->pool);
 }
 
-CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
-                                            request_rec *r)
+CACHE_DECLARE(int) ap_cache_check_allowed(cache_request_rec *cache, request_rec *r) {
+    const char *cc_req;
+    const char *pragma;
+    cache_server_conf *conf =
+      (cache_server_conf *)ap_get_module_config(r->server->module_config,
+                                                &cache_module);
+
+    /*
+     * At this point, we may have data cached, but the request may have
+     * specified that cached data may not be used in a response.
+     *
+     * This is covered under RFC2616 section 14.9.4 (Cache Revalidation and
+     * Reload Controls).
+     *
+     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache, or Pragma:
+     * no-cache. The server MUST NOT use a cached copy when responding to such
+     * a request.
+     *
+     * - RFC2616 14.9.2 What May be Stored by Caches. If Cache-Control:
+     * no-store arrives, do not serve from the cache.
+     */
+
+    /* This value comes from the client's initial request. */
+    cc_req = apr_table_get(r->headers_in, "Cache-Control");
+    pragma = apr_table_get(r->headers_in, "Pragma");
+
+    ap_cache_control(r, &cache->control_in, cc_req, pragma, r->headers_in);
+
+    if (cache->control_in.no_cache) {
+
+        if (!conf->ignorecachecontrol) {
+            return 0;
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                    "Incoming request is asking for an uncached version of "
+                    "%s, but we have been configured to ignore it and serve "
+                    "cached content anyway", r->unparsed_uri);
+        }
+    }
+
+    if (cache->control_in.no_store) {
+
+        if (!conf->ignorecachecontrol) {
+            /* We're not allowed to serve a cached copy */
+            return 0;
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                    "Incoming request is asking for a no-store version of "
+                    "%s, but we have been configured to ignore it and serve "
+                    "cached content anyway", r->unparsed_uri);
+        }
+    }
+
+    return 1;
+}
+
+
+int cache_check_freshness(cache_handle_t *h, cache_request_rec *cache,
+        request_rec *r)
 {
     apr_status_t status;
     apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
     apr_int64_t minfresh;
-    const char *cc_cresp, *cc_req;
+    const char *cc_req;
     const char *pragma;
     const char *agestr = NULL;
-    const char *expstr = NULL;
-    char *val;
     apr_time_t age_c = 0;
     cache_info *info = &(h->cache_obj->info);
     const char *warn_head;
     cache_server_conf *conf =
       (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                 &cache_module);
 
     /*
      * We now want to check if our cached data is still fresh. This depends
      * on a few things, in this order:
      *
-     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache. no-cache in
-     * either the request or the cached response means that we must
-     * revalidate the request unconditionally, overriding any expiration
-     * mechanism. It's equivalent to max-age=0,must-revalidate.
+     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache. no-cache
+     * in either the request or the cached response means that we must
+     * perform the request unconditionally, and ignore cached content. We
+     * should never reach here, but if we do, mark the content as stale,
+     * as this is the best we can do.
      *
      * - RFC2616 14.32 Pragma: no-cache This is treated the same as
      * Cache-Control: no-cache.
      *
      * - RFC2616 14.9.3 Cache-Control: max-stale, must-revalidate,
      * proxy-revalidate if the max-stale request header exists, modify the
