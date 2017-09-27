     apr_shm_t *shm;
     apr_status_t rv;
 
     if (gpool == NULL) {
         return APR_ENOSHMAVAIL;
     }
-    if (name) {
-        if (name[0] == ':') {
-            fname = name;
-        }
-        else {
-            fname = ap_server_root_relative(pool, name);
-        }
-    }
-    else {
+    fname = slotmem_filename(pool, name);
+    if (!fname) {
         return APR_ENOSHMAVAIL;
     }
 
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02301)
+                 "attach looking for %s", fname);
+
     /* first try to attach to existing slotmem */
     if (next) {
         for (;;) {
             if (strcmp(next->name, fname) == 0) {
                 /* we already have it */
                 *new = next;
                 *item_size = next->desc.size;
                 *item_num = next->desc.num;
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                             APLOGNO(02302)
+                             "attach found %s: %"APR_SIZE_T_FMT"/%u", fname,
+                             *item_size, *item_num);
                 return APR_SUCCESS;
             }
             if (!next->next) {
                  break;
             }
             next = next->next;
         }
     }
 
-    /* first try to attach to existing shared memory */
+    /* next try to attach to existing shared memory */
     rv = apr_shm_attach(&shm, fname, gpool);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
     /* Read the description of the slotmem */
