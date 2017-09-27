         }
         else
 #endif
             if (rv == WAIT_FAILED) {
             /* Something serious is wrong */
             ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
-                         ap_server_conf,
-                         "Child %d: WAIT_FAILED -- shutting down server", 
-                         my_pid);
+                         ap_server_conf, APLOGNO(00356)
+                         "Child: WAIT_FAILED -- shutting down server");
             break;
         }
         else if (cld == 0) {
             /* Exit event was signaled */
-            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                         "Child %d: Exit event signaled. Child process is "
-                         "ending.", my_pid);
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00357)
+                         "Child: Exit event signaled. Child process is "
+                         "ending.");
             break;
         }
         else {
-            /* MaxRequestsPerChild event set by the worker threads.
+            /* MaxConnectionsPerChild event set by the worker threads.
              * Signal the parent to restart
              */
-            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                         "Child %d: Process exiting because it reached "
-                         "MaxRequestsPerChild. Signaling the parent to "
-                         "restart a new child process.", my_pid);
+            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00358)
+                         "Child: Process exiting because it reached "
+                         "MaxConnectionsPerChild. Signaling the parent to "
+                         "restart a new child process.");
             ap_signal_parent(SIGNAL_PARENT_RESTART);
             break;
         }
     }
 
     /*
