         ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r, APLOGNO(00693)
                 "cache: No cache request information available for key"
                 " generation");
         return DECLINED;
     }
 
+    /* if no-cache, we can't serve from the cache, but we may store to the
+     * cache.
+     */
+    if (!ap_cache_check_no_cache(cache, r)) {
+        return DECLINED;
+    }
+
     if (!cache->key) {
         rv = cache_generate_key(r, r->pool, &cache->key);
         if (rv != APR_SUCCESS) {
             return DECLINED;
         }
     }
 
-    if (!ap_cache_check_allowed(cache, r)) {
-        return DECLINED;
-    }
-
     /* go through the cache types till we get a match */
     h = apr_palloc(r->pool, sizeof(cache_handle_t));
 
     list = cache->providers;
 
     while (list) {
         switch ((rv = list->provider->open_entity(h, r, cache->key))) {
         case OK: {
             char *vary = NULL;
-            int fresh, mismatch = 0;
+            int mismatch = 0;
+            char *last = NULL;
 
             if (list->provider->recall_headers(h, r) != APR_SUCCESS) {
                 /* try again with next cache type */
                 list = list->next;
                 continue;
             }
