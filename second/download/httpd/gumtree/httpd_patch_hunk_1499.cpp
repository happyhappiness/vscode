 
     cleanup_tables(NULL);
 }
 
 #if APR_HAS_SHARED_MEMORY
 
-static void initialize_tables(server_rec *s, apr_pool_t *ctx)
+static int initialize_tables(server_rec *s, apr_pool_t *ctx)
 {
     unsigned long idx;
     apr_status_t   sts;
+    const char *tempdir; 
 
     /* set up client list */
 
-    sts = apr_shm_create(&client_shm, shmem_size, tmpnam(NULL), ctx);
+    sts = apr_temp_dir_get(&tempdir, ctx);
+    if (APR_SUCCESS != sts) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, 
+                     "Failed to find temporary directory");
+        log_error_and_cleanup("failed to find temp dir", sts, s);
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
+
+    /* Create the shared memory segment */
+
+    /* 
+     * Create a unique filename using our pid. This information is 
+     * stashed in the global variable so the children inherit it.
+     */
+    client_shm_filename = apr_psprintf(ctx, "%s/authdigest_shm.%"APR_PID_T_FMT, tempdir, 
+                                       getpid());
+
+    /* Now create that segment */
+    sts = apr_shm_create(&client_shm, shmem_size,
+                        client_shm_filename, ctx);
+    if (APR_SUCCESS != sts) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, 
+                     "Failed to create shared memory segment on file %s", 
+                     client_shm_filename);
+        log_error_and_cleanup("failed to initialize shm", sts, s);
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
+
+    sts = apr_rmm_init(&client_rmm,
+                       NULL, /* no lock, we'll do the locking ourselves */
+                       apr_shm_baseaddr_get(client_shm),
+                       shmem_size, ctx);
     if (sts != APR_SUCCESS) {
-        log_error_and_cleanup("failed to create shared memory segments", sts, s);
-        return;
+        log_error_and_cleanup("failed to initialize rmm", sts, s);
+        return !OK;
     }
 
-    client_list = apr_rmm_malloc(client_rmm, sizeof(*client_list) +
-                                            sizeof(client_entry*)*num_buckets);
+    client_list = apr_rmm_addr_get(client_rmm, apr_rmm_malloc(client_rmm, sizeof(*client_list) +
+                                                          sizeof(client_entry*)*num_buckets));
     if (!client_list) {
         log_error_and_cleanup("failed to allocate shared memory", -1, s);
-        return;
+        return !OK;
     }
     client_list->table = (client_entry**) (client_list + 1);
     for (idx = 0; idx < num_buckets; idx++) {
         client_list->table[idx] = NULL;
     }
     client_list->tbl_len     = num_buckets;
     client_list->num_entries = 0;
 
-    tmpnam(client_lock_name);
-    /* FIXME: get the client_lock_name from a directive so we're portable
-     * to non-process-inheriting operating systems, like Win32. */
-    sts = apr_global_mutex_create(&client_lock, client_lock_name,
-                                  APR_LOCK_DEFAULT, ctx);
+    sts = ap_global_mutex_create(&client_lock, NULL, client_mutex_type, NULL,
+                                 s, ctx, 0);
     if (sts != APR_SUCCESS) {
         log_error_and_cleanup("failed to create lock (client_lock)", sts, s);
-        return;
+        return !OK;
     }
 
 
     /* setup opaque */
 
-    opaque_cntr = apr_rmm_malloc(client_rmm, sizeof(*opaque_cntr));
+    opaque_cntr = apr_rmm_addr_get(client_rmm, apr_rmm_malloc(client_rmm, sizeof(*opaque_cntr)));
     if (opaque_cntr == NULL) {
         log_error_and_cleanup("failed to allocate shared memory", -1, s);
-        return;
+        return !OK;
     }
     *opaque_cntr = 1UL;
 
-    tmpnam(opaque_lock_name);
-    /* FIXME: get the opaque_lock_name from a directive so we're portable
-     * to non-process-inheriting operating systems, like Win32. */
-    sts = apr_global_mutex_create(&opaque_lock, opaque_lock_name,
-                                  APR_LOCK_DEFAULT, ctx);
+    sts = ap_global_mutex_create(&opaque_lock, NULL, opaque_mutex_type, NULL,
+                                 s, ctx, 0);
     if (sts != APR_SUCCESS) {
         log_error_and_cleanup("failed to create lock (opaque_lock)", sts, s);
-        return;
+        return !OK;
     }
 
 
     /* setup one-time-nonce counter */
 
-    otn_counter = apr_rmm_malloc(client_rmm, sizeof(*otn_counter));
+    otn_counter = apr_rmm_addr_get(client_rmm, apr_rmm_malloc(client_rmm, sizeof(*otn_counter)));
     if (otn_counter == NULL) {
         log_error_and_cleanup("failed to allocate shared memory", -1, s);
-        return;
+        return !OK;
     }
     *otn_counter = 0;
     /* no lock here */
 
 
     /* success */
-    return;
+    return OK;
 }
 
 #endif /* APR_HAS_SHARED_MEMORY */
 
+static int pre_init(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
+{
+    apr_status_t rv;
+
+    rv = ap_mutex_register(pconf, client_mutex_type, NULL, APR_LOCK_DEFAULT, 0);
+    if (rv == APR_SUCCESS) {
+        rv = ap_mutex_register(pconf, opaque_mutex_type, NULL, APR_LOCK_DEFAULT,
+                               0);
+    }
+    if (rv != APR_SUCCESS) {
+        return rv;
+    }
+
+    return OK;
+}
 
 static int initialize_module(apr_pool_t *p, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
 {
     void *data;
     const char *userdata_key = "auth_digest_init";
