 static apr_status_t cleanup_tables(void *not_used)
 {
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                   "Digest: cleaning up shared memory");
     fflush(stderr);
 
+    if (client_rmm) {
+        apr_rmm_destroy(client_rmm);
+        client_rmm = NULL;
+    }
+
     if (client_shm) {
         apr_shm_destroy(client_shm);
         client_shm = NULL;
     }
 
     if (client_lock) {
