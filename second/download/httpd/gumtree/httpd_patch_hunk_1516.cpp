         }
         /* This should not fail, but if it does, we are in BIG trouble
          * cause we just stomped all over the heap.
          */
         AP_DEBUG_ASSERT(obj->count <= mobj->m_len);
     }
+    if (r->connection->aborted && !obj->complete) {
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                     "mem_cache: Discarding body for URL %s "
+                     "because client connection was aborted.",
+                     obj->key);
+        /* No need to cleanup - obj->complete unset, so
+         * decrement_refcount will discard the object */
+        return APR_EGENERAL;
+    }
     return APR_SUCCESS;
 }
 /**
  * Configuration and start-up
  */
 static int mem_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
