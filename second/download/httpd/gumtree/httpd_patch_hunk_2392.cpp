 }
 
 static apr_status_t initialize_secret(server_rec *s)
 {
     apr_status_t status;
 
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
-                 "Digest: generating secret for digest authentication ...");
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01757)
+                 "generating secret for digest authentication ...");
 
 #if APR_HAS_RANDOM
     status = apr_generate_random_bytes(secret, sizeof(secret));
 #else
 #error APR random number support is missing; you probably need to install the truerand library.
 #endif
 
     if (status != APR_SUCCESS) {
         char buf[120];
-        ap_log_error(APLOG_MARK, APLOG_CRIT, status, s,
-                     "Digest: error generating secret: %s",
+        ap_log_error(APLOG_MARK, APLOG_CRIT, status, s, APLOGNO(01758)
+                     "error generating secret: %s",
                      apr_strerror(status, buf, sizeof(buf)));
         return status;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "Digest: done");
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01759) "done");
 
     return APR_SUCCESS;
 }
 
 static void log_error_and_cleanup(char *msg, apr_status_t sts, server_rec *s)
 {
-    ap_log_error(APLOG_MARK, APLOG_ERR, sts, s,
-                 "Digest: %s - all nonce-count checking, one-time nonces, and "
+    ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01760)
+                 "%s - all nonce-count checking, one-time nonces, and "
                  "MD5-sess algorithm disabled", msg);
 
     cleanup_tables(NULL);
 }
 
 #if APR_HAS_SHARED_MEMORY
 
 static int initialize_tables(server_rec *s, apr_pool_t *ctx)
 {
     unsigned long idx;
     apr_status_t   sts;
-    const char *tempdir; 
+    const char *tempdir;
 
     /* set up client list */
 
     sts = apr_temp_dir_get(&tempdir, ctx);
     if (APR_SUCCESS != sts) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, 
+        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01761)
                      "Failed to find temporary directory");
         log_error_and_cleanup("failed to find temp dir", sts, s);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /* Create the shared memory segment */
 
-    /* 
-     * Create a unique filename using our pid. This information is 
+    /*
+     * Create a unique filename using our pid. This information is
      * stashed in the global variable so the children inherit it.
      */
-    client_shm_filename = apr_psprintf(ctx, "%s/authdigest_shm.%"APR_PID_T_FMT, tempdir, 
+    client_shm_filename = apr_psprintf(ctx, "%s/authdigest_shm.%"APR_PID_T_FMT, tempdir,
                                        getpid());
 
     /* Now create that segment */
     sts = apr_shm_create(&client_shm, shmem_size,
                         client_shm_filename, ctx);
     if (APR_SUCCESS != sts) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, 
-                     "Failed to create shared memory segment on file %s", 
+        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01762)
+                     "Failed to create shared memory segment on file %s",
                      client_shm_filename);
         log_error_and_cleanup("failed to initialize shm", sts, s);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     sts = apr_rmm_init(&client_rmm,
