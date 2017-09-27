     cache->out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
     /* save away the possible providers */
     cache->providers = providers;
 
     /*
+     * Are we allowed to serve cached info at all?
+     */
+    if (!ap_cache_check_no_store(cache, r)) {
+        return DECLINED;
+    }
+
+    /* Are we PUT/POST/DELETE? If so, prepare to invalidate the cached entities.
+     */
+    switch (r->method_number) {
+    case M_PUT:
+    case M_POST:
+    case M_DELETE:
+    {
+
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02463)
+                "PUT/POST/DELETE: Adding CACHE_INVALIDATE filter for %s",
+                r->uri);
+
+        /* Add cache_invalidate filter to this request to force a
+         * cache entry to be invalidated if the response is
+         * ultimately successful (2xx).
+         */
+        ap_add_output_filter_handle(
+                cache_invalidate_filter_handle, cache, r,
+                r->connection);
+
+        return DECLINED;
+    }
+    case M_GET: {
+        break;
+    }
+    default : {
+
+        ap_log_rerror(
+                APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02464) "cache: Method '%s' not cacheable by mod_cache, ignoring: %s", r->method, r->uri);
+
+        return DECLINED;
+    }
+    }
+
+    /*
      * Try to serve this request from the cache.
      *
      * If no existing cache file (DECLINED)
      *   add cache_save filter
      * If cached file (OK)
      *   clear filter stack
