 
         }
 
         /* let someone else attempt to cache */
         cache_remove_lock(conf, cache, r, NULL);
 
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02971)
+                    "cache: serving %s (revalidated)", r->uri);
+
         return ap_pass_brigade(f->next, bb);
     }
 
     if (rv != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(00774)
                 "cache: store_headers failed");
