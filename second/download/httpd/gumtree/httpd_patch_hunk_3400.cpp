 
     /* Release the start_mutex to let the new process (in the restart
      * scenario) a chance to begin accepting and servicing requests
      */
     rv = apr_proc_mutex_unlock(start_mutex);
     if (rv == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
-                     "Child %d: Released the start mutex", my_pid);
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00359)
+                     "Child: Released the start mutex");
     }
     else {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
-                     "Child %d: Failure releasing the start mutex", my_pid);
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00360)
+                     "Child: Failure releasing the start mutex");
     }
 
     /* Shutdown the worker threads
      * Post worker threads blocked on the ThreadDispatch IOCompletion port
      */
     while (g_blocked_threads > 0) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
-                     "Child %d: %d threads blocked on the completion port",
-                     my_pid, g_blocked_threads);
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00361)
+                     "Child: %d threads blocked on the completion port",
+                     g_blocked_threads);
         for (i=g_blocked_threads; i > 0; i--) {
-            PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, 
+            PostQueuedCompletionStatus(ThreadDispatchIOCP, 0,
                                        IOCP_SHUTDOWN, NULL);
         }
         Sleep(1000);
     }
     /* Empty the accept queue of completion contexts */
     apr_thread_mutex_lock(qlock);
