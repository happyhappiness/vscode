 
 
     /* TODO: Update stats file (!) */
     rv = apr_file_mktemp(&fp, path, APR_CREATE | APR_WRITE, pool);
 
     if (rv) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: Unable to open tmp file: %s", path);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02074)
+                     "Unable to open tmp file: %s", path);
         return rv;
     }
     rv = apr_file_open(&fpin, ctx->storage_path, APR_READ|APR_BINARY|APR_BUFFERED,
                        APR_OS_DEFAULT, pool);
 
     now = apr_time_now();
     if (rv == APR_SUCCESS) {
         char *t;
         apr_table_t *hbt = apr_table_make(pool, 10);
-        apr_bucket_alloc_t *ba = apr_bucket_alloc_create(pool);
-        apr_bucket_brigade *bb = apr_brigade_create(pool, ba);
-        apr_bucket_brigade *tmpbb = apr_brigade_create(pool, ba);
+        apr_bucket_alloc_t *ba;
+        apr_bucket_brigade *bb;
+        apr_bucket_brigade *tmpbb;
+
         rv = apr_file_info_get(&fi, APR_FINFO_SIZE | APR_FINFO_MTIME, fpin);
         if (rv) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                         "Heartmonitor: Unable to read file: %s", ctx->storage_path);
+            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02075)
+                         "Unable to read file: %s", ctx->storage_path);
             return rv;
         }
 
         /* Read the file and update the line corresponding to the node */
         ba = apr_bucket_alloc_create(pool);
         bb = apr_brigade_create(pool, ba);
