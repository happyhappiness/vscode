             if ( pidfile != NULL && unlink(pidfile) == 0)
                 ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                              ap_server_conf,
                              "removed PID file %s (pid=%" APR_PID_T_FMT ")",
                              pidfile, getpid());
 
-            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
-                         ap_server_conf, "caught SIGTERM, shutting down");
+            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+                         "caught " AP_SIG_GRACEFUL_STOP_STRING
+                         ", shutting down gracefully");
+        }
+
+        if (ap_graceful_shutdown_timeout) {
+            cutoff = apr_time_now() +
+                     apr_time_from_sec(ap_graceful_shutdown_timeout);
         }
 
         /* Don't really exit until each child has finished */
         shutdown_pending = 0;
         do {
             /* Pause for a second */
