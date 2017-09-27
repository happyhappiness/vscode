     }
     else if (r->no_cache) {
         /* or we've been asked not to cache it above */
         reason = "r->no_cache present";
     }
 
+    /* Hold the phone. Some servers might allow us to cache a 2xx, but
+     * then make their 304 responses non cacheable. This leaves us in a
+     * sticky position. If the 304 is in answer to our own conditional
+     * request, we cannot send this 304 back to the client because the
+     * client isn't expecting it. Instead, our only option is to respect
+     * the answer to the question we asked (has it changed, answer was
+     * no) and return the cached item to the client, and then respect
+     * the uncacheable nature of this 304 by allowing the remove_url
+     * filter to kick in and remove the cached entity.
+     */
+    if (reason && r->status == HTTP_NOT_MODIFIED &&
+             cache->stale_handle) {
+        apr_bucket_brigade *bb;
+        apr_bucket *bkt;
+        int status;
+
+        cache->handle = cache->stale_handle;
+        info = &cache->handle->cache_obj->info;
+
+        /* Load in the saved status and clear the status line. */
+        r->status = info->status;
+        r->status_line = NULL;
+
+        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+
+        r->headers_in = cache->stale_headers;
+        status = ap_meets_conditions(r);
+        if (status != OK) {
+            r->status = status;
+
+            bkt = apr_bucket_flush_create(bb->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(bb, bkt);
+        }
+        else {
+            cache->provider->recall_body(cache->handle, r->pool, bb);
+        }
+
+        cache->block_response = 1;
+
+        /* let someone else attempt to cache */
+        ap_cache_remove_lock(conf, r, cache->handle ?
+                (char *)cache->handle->cache_obj->key : NULL, NULL);
+
+        return ap_pass_brigade(f->next, bb);
+    }
+
     if (reason) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "cache: %s not cached. Reason: %s", r->unparsed_uri,
                      reason);
 
         /* remove this filter from the chain */
