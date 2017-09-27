      *      the parent process creates other children and passes the pipes
      *      to our worker processes, then we have no business doing such
      *      things in the child_main loop, but should happen in master_main.
      */
     while (1) {
 #if !APR_HAS_OTHER_CHILD
-        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, INFINITE);
+        rv = WaitForMultipleObjects(2, (HANDLE *)child_events, FALSE, INFINITE);
         cld = rv - WAIT_OBJECT_0;
 #else
-        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, 1000);
+        rv = WaitForMultipleObjects(2, (HANDLE *)child_events, FALSE, 1000);
         cld = rv - WAIT_OBJECT_0;
         if (rv == WAIT_TIMEOUT) {
             apr_proc_other_child_refresh_all(APR_OC_REASON_RUNNING);
         }
         else
 #endif
             if (rv == WAIT_FAILED) {
             /* Something serious is wrong */
-            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
-                         "Child %lu: WAIT_FAILED -- shutting down server", my_pid);
+            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
+                         ap_server_conf,
+                         "Child %d: WAIT_FAILED -- shutting down server", 
+                         my_pid);
             break;
         }
         else if (cld == 0) {
             /* Exit event was signaled */
             ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                         "Child %lu: Exit event signaled. Child process is ending.", my_pid);
+                         "Child %d: Exit event signaled. Child process is "
+                         "ending.", my_pid);
             break;
         }
         else {
             /* MaxRequestsPerChild event set by the worker threads.
              * Signal the parent to restart
              */
             ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                         "Child %lu: Process exiting because it reached "
+                         "Child %d: Process exiting because it reached "
                          "MaxRequestsPerChild. Signaling the parent to "
                          "restart a new child process.", my_pid);
             ap_signal_parent(SIGNAL_PARENT_RESTART);
             break;
         }
     }
