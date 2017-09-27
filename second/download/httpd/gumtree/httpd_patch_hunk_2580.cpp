                             s->ip, s->ready, s->busy, (unsigned int) seen, s->port);
         }
     }
 
     rv = apr_file_flush(fp);
     if (rv) {
-      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                   "Heartmonitor: Unable to flush file: %s", path);
+      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02082)
+                   "Unable to flush file: %s", path);
       return rv;
     }
 
     rv = apr_file_close(fp);
     if (rv) {
-      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                   "Heartmonitor: Unable to close file: %s", path);
+      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02083)
+                   "Unable to close file: %s", path);
       return rv;
     }
-  
+
     rv = apr_file_perms_set(path,
                             APR_FPROT_UREAD | APR_FPROT_GREAD |
                             APR_FPROT_WREAD);
-    if (rv && rv != APR_INCOMPLETE) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: Unable to set file permssions on %s",
+    if (rv && rv != APR_INCOMPLETE && rv != APR_ENOTIMPL) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02084)
+                     "Unable to set file permissions on %s",
                      path);
         return rv;
     }
 
     rv = apr_file_rename(path, ctx->storage_path, p);
 
     if (rv) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: Unable to move file: %s -> %s", path,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02085)
+                     "Unable to move file: %s -> %s", path,
                      ctx->storage_path);
         return rv;
     }
 
     return APR_SUCCESS;
 }
