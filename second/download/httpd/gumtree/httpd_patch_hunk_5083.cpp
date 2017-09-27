         }
         if (AP_SLOTMEM_IS_CLEARINUSE(slotmem)) {
             slotmem_clearinuse(slotmem);
         }
         nbytes = (slotmem->desc.size * slotmem->desc.num) +
                  (slotmem->desc.num * sizeof(char)) + AP_UNSIGNEDINT_OFFSET;
-        /* XXX: Error handling */
-        apr_file_write_full(fp, slotmem->persist, nbytes, NULL);
+        apr_md5(digest, slotmem->persist, nbytes);
+        rv = apr_file_write_full(fp, slotmem->persist, nbytes, NULL);
+        if (rv == APR_SUCCESS) {
+            rv = apr_file_write_full(fp, digest, APR_MD5_DIGESTSIZE, NULL);
+        }
         apr_file_close(fp);
+        if (rv != APR_SUCCESS) {
+            apr_file_remove(storename, slotmem->gpool);
+        }
     }
 }
 
-/* should be apr_status_t really */
-static void restore_slotmem(void *ptr, const char *name, apr_size_t size,
-                            apr_pool_t *pool)
+static apr_status_t restore_slotmem(void *ptr, const char *name, apr_size_t size,
+                                    apr_pool_t *pool)
 {
     const char *storename;
     apr_file_t *fp;
     apr_size_t nbytes = size;
-    apr_status_t rv;
+    apr_status_t rv = APR_SUCCESS;
+    unsigned char digest[APR_MD5_DIGESTSIZE];
+    unsigned char digest2[APR_MD5_DIGESTSIZE];
 
     storename = slotmem_filename(pool, name, 1);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02335)
                  "restoring %s", storename);
 
     if (storename) {
         rv = apr_file_open(&fp, storename, APR_READ | APR_WRITE, APR_OS_DEFAULT,
                            pool);
         if (rv == APR_SUCCESS) {
-            apr_finfo_t fi;
-            if (apr_file_info_get(&fi, APR_FINFO_SIZE, fp) == APR_SUCCESS) {
-                if (fi.size == nbytes) {
-                    apr_file_read(fp, ptr, &nbytes);
+            rv = apr_file_read(fp, ptr, &nbytes);
+            if ((rv == APR_SUCCESS || rv == APR_EOF) && nbytes == size) {
+                rv = APR_SUCCESS;   /* for successful return @ EOF */
+                /*
+                 * if at EOF, don't bother checking md5
+                 *  - backwards compatibility
+                 *  */
+                if (apr_file_eof(fp) != APR_EOF) {
+                    apr_size_t ds = APR_MD5_DIGESTSIZE;
+                    rv = apr_file_read(fp, digest, &ds);
+                    if ((rv == APR_SUCCESS || rv == APR_EOF) &&
+                        ds == APR_MD5_DIGESTSIZE) {
+                        rv = APR_SUCCESS;
+                        apr_md5(digest2, ptr, nbytes);
+                        if (memcmp(digest, digest2, APR_MD5_DIGESTSIZE)) {
+                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                                         APLOGNO(02551) "bad md5 match");
+                            rv = APR_EGENERAL;
+                        }
+                    }
                 }
                 else {
-                    apr_file_close(fp);
-                    apr_file_remove(storename, pool);
-                    return;
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                                 APLOGNO(02552) "at EOF... bypassing md5 match check (old persist file?)");
                 }
             }
+            else if (nbytes != size) {
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                             APLOGNO(02553) "Expected %" APR_SIZE_T_FMT ": Read %" APR_SIZE_T_FMT,
+                             size, nbytes);
+                rv = APR_EGENERAL;
+            }
             apr_file_close(fp);
         }
     }
+    return rv;
 }
 
 static apr_status_t cleanup_slotmem(void *param)
 {
     ap_slotmem_instance_t **mem = param;
 
