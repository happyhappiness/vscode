                      */
                     cache->remove_url_filter =
                         ap_add_output_filter_handle(cache_remove_url_filter_handle,
                                 cache, r, r->connection);
                 }
                 else {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, rv,
-                                 r->server, "Cache locked for url, not caching "
-                                 "response: %s", r->uri);
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
+                            r, APLOGNO(00752) "Cache locked for url, not caching "
+                            "response: %s", r->uri);
                 }
             }
             else {
                 if (cache->stale_headers) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
-                                 r->server, "Restoring request headers for %s",
-                                 r->uri);
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
+                            r, APLOGNO(00753) "Restoring request headers for %s",
+                            r->uri);
 
                     r->headers_in = cache->stale_headers;
                 }
-
-                /* Delete our per-request configuration. */
-                ap_set_module_config(r->request_config, &cache_module, NULL);
             }
         }
         else {
             /* error */
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                         "cache: error returned while checking for cached "
-                         "file by '%s' cache", cache->provider_name);
+            return rv;
         }
         return DECLINED;
     }
 
+    /* we've got a cache hit! tell everyone who cares */
+    cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_HIT,
+            "cache hit");
+
     /* if we are a lookup, we are exiting soon one way or another; Restore
      * the headers. */
     if (lookup) {
         if (cache->stale_headers) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
-                         "Restoring request headers.");
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00754)
+                    "Restoring request headers.");
             r->headers_in = cache->stale_headers;
         }
-
-        /* Delete our per-request configuration. */
-        ap_set_module_config(r->request_config, &cache_module, NULL);
     }
 
     rv = ap_meets_conditions(r);
     if (rv != OK) {
         /* If we are a lookup, we have to return DECLINED as we have no
          * way of knowing if we will be able to serve the content.
