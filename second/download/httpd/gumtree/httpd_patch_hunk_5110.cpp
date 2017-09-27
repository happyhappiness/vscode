             /* Exit event was signaled */
             ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00357)
                          "Child: Exit event signaled. Child process is "
                          "ending.");
             break;
         }
+        else if (cld == 2) {
+            /* The parent is dead.  Shutdown the child process. */
+            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(02538)
+                         "Child: Parent process exited abruptly. Child process "
+                         "is ending");
+            break;
+        }
         else {
             /* MaxConnectionsPerChild event set by the worker threads.
              * Signal the parent to restart
              */
             ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00358)
                          "Child: Process exiting because it reached "
