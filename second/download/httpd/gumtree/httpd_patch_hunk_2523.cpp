                 cache->remove_url_filter =
                     ap_add_output_filter_handle(cache_remove_url_filter_handle,
                             cache, r, r->connection);
 
             }
             else {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv,
-                             r->server, "Cache locked for url, not caching "
-                             "response: %s", r->uri);
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
+                        r, APLOGNO(00760) "Cache locked for url, not caching "
+                        "response: %s", r->uri);
             }
         }
         else {
             /* error */
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                         "cache: error returned while checking for cached "
-                         "file by %s cache", cache->provider_name);
+            return rv;
         }
         return DECLINED;
     }
 
+    /* we've got a cache hit! tell everyone who cares */
+    cache_run_cache_status(cache->handle, r, r->headers_out, AP_CACHE_HIT,
+            "cache hit");
+
     rv = ap_meets_conditions(r);
     if (rv != OK) {
         return rv;
     }
 
     /* Serve up the content */
