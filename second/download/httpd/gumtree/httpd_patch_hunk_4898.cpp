  * none      : no persistent data
  * rel_name  : $server_root/rel_name
  * /abs_name : $abs_name
  *
  */
 
-static const char *slotmem_filename(apr_pool_t *pool, const char *slotmemname)
+static const char *slotmem_filename(apr_pool_t *pool, const char *slotmemname,
+                                    int persist)
 {
     const char *fname;
     if (!slotmemname || strcasecmp(slotmemname, "none") == 0) {
         return NULL;
     }
     else if (slotmemname[0] != '/') {
         const char *filenm = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
-                                       slotmemname, DEFAULT_SLOTMEM_SUFFIX, NULL);
+                                         slotmemname, DEFAULT_SLOTMEM_SUFFIX,
+                                         NULL);
         fname = ap_runtime_dir_relative(pool, filenm);
     }
     else {
         fname = slotmemname;
     }
+
+    if (persist) {
+        return apr_pstrcat(pool, fname, DEFAULT_SLOTMEM_PERSIST_SUFFIX,
+                           NULL);
+    }
     return fname;
 }
 
+static void slotmem_clearinuse(ap_slotmem_instance_t *slot)
+{
+    unsigned int i;
+    char *inuse;
+    
+    if (!slot) {
+        return;
+    }
+    
+    inuse = slot->inuse;
+    
+    for (i = 0; i < slot->desc.num; i++, inuse++) {
+        if (*inuse) {
+            *inuse = 0;
+            (*slot->num_free)++;
+        }
+    }
+}
+
 static void store_slotmem(ap_slotmem_instance_t *slotmem)
 {
     apr_file_t *fp;
     apr_status_t rv;
     apr_size_t nbytes;
     const char *storename;
 
-    storename = slotmem_filename(slotmem->gpool, slotmem->name);
+    storename = slotmem_filename(slotmem->gpool, slotmem->name, 1);
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02334)
+                 "storing %s", storename);
 
     if (storename) {
         rv = apr_file_open(&fp, storename, APR_CREATE | APR_READ | APR_WRITE,
                            APR_OS_DEFAULT, slotmem->gpool);
         if (APR_STATUS_IS_EEXIST(rv)) {
             apr_file_remove(storename, slotmem->gpool);
             rv = apr_file_open(&fp, storename, APR_CREATE | APR_READ | APR_WRITE,
                                APR_OS_DEFAULT, slotmem->gpool);
         }
         if (rv != APR_SUCCESS) {
             return;
         }
+        if (AP_SLOTMEM_IS_CLEARINUSE(slotmem)) {
+            slotmem_clearinuse(slotmem);
+        }
         nbytes = (slotmem->desc.size * slotmem->desc.num) +
                  (slotmem->desc.num * sizeof(char)) + AP_UNSIGNEDINT_OFFSET;
-        apr_file_write(fp, slotmem->persist, &nbytes);
+        /* XXX: Error handling */
+        apr_file_write_full(fp, slotmem->persist, nbytes, NULL);
         apr_file_close(fp);
     }
 }
 
 /* should be apr_status_t really */
 static void restore_slotmem(void *ptr, const char *name, apr_size_t size,
