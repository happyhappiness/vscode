                          "restart a new child process.", my_pid);
             ap_signal_parent(SIGNAL_PARENT_RESTART);
             break;
         }
     }
 
-    /* 
-     * Time to shutdown the child process 
+    /*
+     * Time to shutdown the child process
      */
 
  shutdown:
 
     winnt_mpm_state = AP_MPMQ_STOPPING;
-    /* Setting is_graceful will cause threads handling keep-alive connections 
+    /* Setting is_graceful will cause threads handling keep-alive connections
      * to close the connection after handling the current request.
      */
     is_graceful = 1;
 
     /* Close the listening sockets. Note, we must close the listeners
      * before closing any accept sockets pending in AcceptEx to prevent
      * memory leaks in the kernel.
      */
     for (lr = ap_listeners; lr ; lr = lr->next) {
         apr_socket_close(lr->sd);
     }
 
-    /* Shutdown listener threads and pending AcceptEx socksts 
+    /* Shutdown listener threads and pending AcceptEx socksts
      * but allow the worker threads to continue consuming from
      * the queue of accepted connections.
      */
     shutdown_in_progress = 1;
 
     Sleep(1000);
 
     /* Tell the worker threads to exit */
     workers_may_exit = 1;
 
     /* Release the start_mutex to let the new process (in the restart
-     * scenario) a chance to begin accepting and servicing requests 
+     * scenario) a chance to begin accepting and servicing requests
      */
     rv = apr_proc_mutex_unlock(start_mutex);
     if (rv == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK,APLOG_NOTICE, rv, ap_server_conf, 
+        ap_log_error(APLOG_MARK,APLOG_NOTICE, rv, ap_server_conf,
                      "Child %d: Released the start mutex", my_pid);
     }
     else {
-        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, 
+        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                      "Child %d: Failure releasing the start mutex", my_pid);
     }
 
     /* Shutdown the worker threads */
     if (!use_acceptex) {
         for (i = 0; i < threads_created; i++) {
             add_job(INVALID_SOCKET);
         }
     }
     else { /* Windows NT/2000 */
         /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
         while (g_blocked_threads > 0) {
-            ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf, 
+            ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf,
                          "Child %d: %d threads blocked on the completion port", my_pid, g_blocked_threads);
             for (i=g_blocked_threads; i > 0; i--) {
                 PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_SHUTDOWN, NULL);
             }
             Sleep(1000);
         }
