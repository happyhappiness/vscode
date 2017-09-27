     /* Initialize the cache_handle */
     h->cache_obj = obj;
     h->req_hdrs = NULL;  /* Pick these up in recall_headers() */
     return OK;
 }
 
+/* remove_entity()
+ * Notes: 
+ *   refcount should be at least 1 upon entry to this function to account
+ *   for this thread's reference to the object. If the refcount is 1, then
+ *   object has been removed from the cache by another thread and this thread
+ *   is the last thread accessing the object.
+ */
 static int remove_entity(cache_handle_t *h) 
 {
     cache_object_t *obj = h->cache_obj;
+    cache_object_t *tobj = NULL;
 
-    /* Remove the cache object from the cache under protection */
     if (sconf->lock) {
         apr_thread_mutex_lock(sconf->lock);
     }
-    /* If the object is not already marked for cleanup, remove
-     * it from the cache and mark it for cleanup. Remember,
-     * an object marked for cleanup is by design not in the
-     * hash table.
+
+    /* If the entity is still in the cache, remove it and decrement the
+     * refcount. If the entity is not in the cache, do nothing. In both cases
+     * decrement_refcount called by the last thread referencing the object will 
+     * trigger the cleanup.
      */
-    if (!obj->cleanup) {
+    tobj = cache_find(sconf->cache_cache, obj->key);
+    if (tobj == obj) {
         cache_remove(sconf->cache_cache, obj);
-        obj->cleanup = 1;
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, "gcing a cache entry");
+        apr_atomic_dec(&obj->refcount);
     }
-
+    
     if (sconf->lock) {
         apr_thread_mutex_unlock(sconf->lock);
     }
 
     return OK;
 }
