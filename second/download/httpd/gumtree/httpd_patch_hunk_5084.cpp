         memset(ptr, 0, dsize);
         /*
          * TODO: Error check the below... What error makes
          * sense if the restore fails? Any?
          */
         if (type & AP_SLOTMEM_TYPE_PERSIST) {
-            restore_slotmem(ptr, fname, dsize, pool);
-            restored = 1;
+            rv = restore_slotmem(ptr, fname, dsize, pool);
+            if (rv == APR_SUCCESS) {
+                restored = 1;
+            }
+            else {
+                /* just in case, re-zero */
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                             APLOGNO(02554) "could not restore %s", fname);
+                memset(ptr, 0, dsize);
+            }
         }
     }
 
     /* For the chained slotmem stuff */
     res = (ap_slotmem_instance_t *) apr_pcalloc(gpool,
                                                 sizeof(ap_slotmem_instance_t));
