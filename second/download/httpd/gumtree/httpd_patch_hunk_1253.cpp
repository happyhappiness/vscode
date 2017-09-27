          */
         rv = cache->provider->store_body(cache->handle, r, in);
         if (rv != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                          "cache: Cache provider's store_body failed!");
             ap_remove_output_filter(f);
+
+            /* give someone else the chance to cache the file */
+            ap_cache_remove_lock(conf, r, cache->handle ?
+                    (char *)cache->handle->cache_obj->key : NULL, NULL);
         }
+        else {
+
+        	/* proactively remove the lock as soon as we see the eos bucket */
+            ap_cache_remove_lock(conf, r, cache->handle ?
+                    (char *)cache->handle->cache_obj->key : NULL, in);
+
+        }
+
         return ap_pass_brigade(f->next, in);
     }
 
     /*
      * Setup Data in Cache
      * -------------------
