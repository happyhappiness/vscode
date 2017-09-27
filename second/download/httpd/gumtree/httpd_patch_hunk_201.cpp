         rv = apr_file_open(&fd, fname, xfer_flags, xfer_perms, p);
         if (rv != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                             "could not open transfer log file %s.", fname);
             return NULL;
         }
-        apr_file_inherit_set(fd);
         return fd;
     }
 }
 static void *ap_buffered_log_writer_init(apr_pool_t *p, server_rec *s, 
                                         const char* name)
 {
     buffered_log *b;
-    b = apr_palloc(p, sizeof(buffered_log));
+    b = apr_pcalloc(p, sizeof(buffered_log));
     b->handle = ap_default_log_writer_init(p, s, name);
-    b->outcnt = 0;
     
-    if (b->handle)
+    if (b->handle) {
+        *(buffered_log **)apr_array_push(all_buffered_logs) = b;
         return b;
+    }
     else
         return NULL;
 }
 static apr_status_t ap_buffered_log_writer(request_rec *r,
                                            void *handle, 
                                            const char **strs,
