          */
         if (!r->filename) {
             return DECLINED;
         }
     }
 
-    /* Allocate and initialize cache_object_t */
-    obj = calloc(1, sizeof(*obj));
-    if (!obj) {
-        return DECLINED;
-    }
-    key_len = strlen(key) + 1;
-    obj->key = malloc(key_len);
-    if (!obj->key) {
-        cleanup_cache_object(obj);
+    rv = apr_pool_create(&pool, NULL);
+
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
+                     "mem_cache: Failed to create memory pool.");
         return DECLINED;
     }
-    memcpy((void*)obj->key, key, key_len);
+
+    /* Allocate and initialize cache_object_t */
+    obj = apr_pcalloc(pool, sizeof(*obj));
+    obj->key = apr_pstrdup(pool, key);
 
     /* Allocate and init mem_cache_object_t */
-    mobj = calloc(1, sizeof(*mobj));
-    if (!mobj) {
-        cleanup_cache_object(obj);
-        return DECLINED;
-    }
+    mobj = apr_pcalloc(pool, sizeof(*mobj));
+    mobj->pool = pool;
 
     /* Finish initing the cache object */
     apr_atomic_set32(&obj->refcount, 1);
     mobj->total_refs = 1;
     obj->complete = 0;
     obj->vobj = mobj;
