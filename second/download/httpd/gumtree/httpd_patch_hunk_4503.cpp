      * Create a unique filename using our pid. This information is
      * stashed in the global variable so the children inherit it.
      */
     client_shm_filename = ap_runtime_dir_relative(ctx, "authdigest_shm");
     client_shm_filename = ap_append_pid(ctx, client_shm_filename, ".");
 
-    /* Now create that segment */
-    sts = apr_shm_create(&client_shm, shmem_size,
-                        client_shm_filename, ctx);
+    /* Use anonymous shm by default, fall back on name-based. */
+    sts = apr_shm_create(&client_shm, shmem_size, NULL, ctx);
+    if (APR_STATUS_IS_ENOTIMPL(sts)) {
+        /* For a name-based segment, remove it first in case of a
+         * previous unclean shutdown. */
+        apr_shm_remove(client_shm_filename, ctx);
+
+        /* Now create that segment */
+        sts = apr_shm_create(&client_shm, shmem_size,
+                            client_shm_filename, ctx);
+    }
+
     if (APR_SUCCESS != sts) {
         ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01762)
                      "Failed to create shared memory segment on file %s",
                      client_shm_filename);
         log_error_and_cleanup("failed to initialize shm", sts, s);
         return HTTP_INTERNAL_SERVER_ERROR;
