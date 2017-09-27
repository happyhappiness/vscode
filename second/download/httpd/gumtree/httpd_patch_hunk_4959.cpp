     /* Was this the final bucket? If yes, close the temp file and perform
      * sanity checks.
      */
     if (seen_eos) {
         const char *cl_header = apr_table_get(r->headers_out, "Content-Length");
 
-        if (dobj->data.tempfd) {
-            rv = apr_file_close(dobj->data.tempfd);
-            if (rv != APR_SUCCESS) {
-                /* Buffered write failed, abandon attempt to write */
-                apr_pool_destroy(dobj->data.pool);
-                return rv;
+        if (!dobj->disk_info.header_only) {
+
+            if (dobj->data.tempfd) {
+                rv = apr_file_close(dobj->data.tempfd);
+                if (rv != APR_SUCCESS) {
+                    /* Buffered write failed, abandon attempt to write */
+                    apr_pool_destroy(dobj->data.pool);
+                    return rv;
+                }
             }
-        }
 
-        if (r->connection->aborted || r->no_cache) {
-            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00733)
-                    "Discarding body for URL %s "
-                    "because connection has been aborted.",
-                    h->cache_obj->key);
-            /* Remove the intermediate cache file and return non-APR_SUCCESS */
-            apr_pool_destroy(dobj->data.pool);
-            return APR_EGENERAL;
-        }
-        if (dobj->file_size < dconf->minfs) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00734)
-                    "URL %s failed the size check "
-                    "(%" APR_OFF_T_FMT "<%" APR_OFF_T_FMT ")",
-                    h->cache_obj->key, dobj->file_size, dconf->minfs);
-            /* Remove the intermediate cache file and return non-APR_SUCCESS */
-            apr_pool_destroy(dobj->data.pool);
-            return APR_EGENERAL;
-        }
-        if (cl_header) {
-            apr_int64_t cl = apr_atoi64(cl_header);
-            if ((errno == 0) && (dobj->file_size != cl)) {
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00735)
-                        "URL %s didn't receive complete response, not caching",
-                        h->cache_obj->key);
+            if (r->connection->aborted || r->no_cache) {
+                ap_log_rerror(
+                        APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00733) "Discarding body for URL %s "
+                        "because connection has been aborted.", h->cache_obj->key);
                 /* Remove the intermediate cache file and return non-APR_SUCCESS */
                 apr_pool_destroy(dobj->data.pool);
                 return APR_EGENERAL;
             }
+            if (dobj->file_size < dconf->minfs) {
+                ap_log_rerror(
+                        APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00734) "URL %s failed the size check "
+                        "(%" APR_OFF_T_FMT "<%" APR_OFF_T_FMT ")", h->cache_obj->key, dobj->file_size, dconf->minfs);
+                /* Remove the intermediate cache file and return non-APR_SUCCESS */
+                apr_pool_destroy(dobj->data.pool);
+                return APR_EGENERAL;
+            }
+            if (cl_header) {
+                apr_int64_t cl = apr_atoi64(cl_header);
+                if ((errno == 0) && (dobj->file_size != cl)) {
+                    ap_log_rerror(
+                            APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00735) "URL %s didn't receive complete response, not caching", h->cache_obj->key);
+                    /* Remove the intermediate cache file and return non-APR_SUCCESS */
+                    apr_pool_destroy(dobj->data.pool);
+                    return APR_EGENERAL;
+                }
+            }
+
         }
 
         /* All checks were fine, we're good to go when the commit comes */
     }
 
     return APR_SUCCESS;
