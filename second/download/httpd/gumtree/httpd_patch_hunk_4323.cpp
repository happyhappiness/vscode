      * different entity, to be safe, we remove the entity from the cache.
      */
     if (reason && r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {
 
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02473) 
                 "cache: %s responded with an uncacheable 304, " 
-                "retrying the request. Reason: %s", 
-                r->unparsed_uri, reason);
+                "retrying the request %s. Reason: %s", 
+                cache->key, r->unparsed_uri, reason);
 
         /* we've got a cache conditional miss! tell anyone who cares */
         cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_MISS,
                 apr_psprintf(r->pool,
                         "conditional cache miss: 304 was uncacheable, entity removed: %s",
                         reason));
