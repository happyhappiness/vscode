                          ap_daemons_limit);
         }
         ap_daemons_limit = 1;
     }
 
     /* ap_daemons_to_start > ap_daemons_limit checked in prefork_run() */
-    if (ap_daemons_to_start < 0) {
+    if (ap_daemons_to_start < 1) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00184)
                          "WARNING: StartServers of %d not allowed, "
                          "increasing to 1.", ap_daemons_to_start);
         } else {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00185)
