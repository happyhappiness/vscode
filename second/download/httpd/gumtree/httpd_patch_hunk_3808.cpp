         ptr += AP_SLOTMEM_OFFSET;
         memset(ptr, 0, dsize);
         /*
          * TODO: Error check the below... What error makes
          * sense if the restore fails? Any?
          */
-        if (type & AP_SLOTMEM_TYPE_PERSIST) {
-            rv = restore_slotmem(ptr, fname, dsize, pool);
+        if (persist) {
+            rv = restore_slotmem(ptr, pname, dsize, pool);
             if (rv == APR_SUCCESS) {
                 restored = 1;
             }
             else {
                 /* just in case, re-zero */
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
