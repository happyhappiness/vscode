     if (restart_num++ == 0) {
         startup = 1;
     }
 
     if (ap_daemons_to_start < 0) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00213)
                          "WARNING: StartServers of %d not allowed, "
                          "increasing to 1.", ap_daemons_to_start);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00214)
                          "StartServers of %d not allowed, increasing to 1",
                          ap_daemons_to_start);
         }
         ap_daemons_to_start = 1;
     }
 
     if (ap_min_spare_threads < 1) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00215)
                          "WARNING: MinSpareThreads of %d not allowed, "
                          "increasing to 1", ap_min_spare_threads);
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                          " to avoid almost certain server failure.");
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                          " Please read the documentation.");
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00216)
                          "MinSpareThreads of %d not allowed, increasing to 1",
                          ap_min_spare_threads);
         }
         ap_min_spare_threads = 1;
     }
 
