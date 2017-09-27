         return rv;
     }
 
 #if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
     rv = apr_env_get(&logpath, "APR_POOL_DEBUG_LOG", global_pool);
 
+    /* Don't pass file_stderr directly to apr_file_open() here, since
+     * apr_file_open() can call back to apr_pool_log_event() and that
+     * may attempt to use then then non-NULL but partially set up file
+     * object. */
     if (rv == APR_SUCCESS) {
-        apr_file_open(&file_stderr, logpath, APR_APPEND|APR_WRITE|APR_CREATE,
+        apr_file_open(&debug_log, logpath, APR_APPEND|APR_WRITE|APR_CREATE,
                       APR_OS_DEFAULT, global_pool);
     }
     else {
-        apr_file_open_stderr(&file_stderr, global_pool);
+        apr_file_open_stderr(&debug_log, global_pool);
     }
 
+    /* debug_log is now a file handle. */
+    file_stderr = debug_log;
+
     if (file_stderr) {
         apr_file_printf(file_stderr,
             "POOL DEBUG: [PID"
 #if APR_HAS_THREADS
             "/TID"
 #endif /* APR_HAS_THREADS */
