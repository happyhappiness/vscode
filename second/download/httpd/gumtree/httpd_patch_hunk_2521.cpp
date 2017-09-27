      *   add cache_save filter
      * If cached file (OK)
      *   clear filter stack
      *   add cache_out filter
      *   return OK
      */
-    rv = cache_select(r);
+    rv = cache_select(cache, r);
     if (rv != OK) {
         if (rv == DECLINED) {
 
             /* try to obtain a cache lock at this point. if we succeed,
              * we are the first to try and cache this url. if we fail,
              * it means someone else is already trying to cache this
              * url, and we should just let the request through to the
              * backend without any attempt to cache. this stops
              * duplicated simultaneous attempts to cache an entity.
              */
-            rv = ap_cache_try_lock(conf, r, NULL);
+            rv = cache_try_lock(conf, cache, r);
             if (APR_SUCCESS == rv) {
 
                 /*
                  * Add cache_save filter to cache this request. Choose
                  * the correct filter by checking if we are a subrequest
                  * or not.
                  */
                 if (r->main) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
-                            r->server,
-                            "Adding CACHE_SAVE_SUBREQ filter for %s",
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
+                            r, APLOGNO(00756) "Adding CACHE_SAVE_SUBREQ filter for %s",
                             r->uri);
                     cache_save_handle = cache_save_subreq_filter_handle;
                 }
                 else {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
-                            r->server, "Adding CACHE_SAVE filter for %s",
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
+                            r, APLOGNO(00757) "Adding CACHE_SAVE filter for %s",
                             r->uri);
                     cache_save_handle = cache_save_filter_handle;
                 }
-                ap_add_output_filter_handle(cache_save_handle,
-                        NULL, r, r->connection);
+                ap_add_output_filter_handle(cache_save_handle, cache, r,
+                        r->connection);
 
                 /*
                  * Did the user indicate the precise location of the
                  * CACHE_SAVE filter by inserting the CACHE filter as a
                  * marker?
                  *
