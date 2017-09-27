      */
     if ((rv = apr_atomic_init(global_pool)) != APR_SUCCESS) {
         return rv;
     }
 
 #if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
-    apr_file_open_stderr(&file_stderr, global_pool);
+    rv = apr_env_get(&logpath, "APR_POOL_DEBUG_LOG", global_pool);
+
+    if (rv == APR_SUCCESS) {
+        apr_file_open(&file_stderr, logpath, APR_APPEND|APR_WRITE|APR_CREATE,
+                      APR_OS_DEFAULT, global_pool);
+    }
+    else {
+        apr_file_open_stderr(&file_stderr, global_pool);
+    }
+
     if (file_stderr) {
         apr_file_printf(file_stderr,
             "POOL DEBUG: [PID"
 #if APR_HAS_THREADS
             "/TID"
 #endif /* APR_HAS_THREADS */
