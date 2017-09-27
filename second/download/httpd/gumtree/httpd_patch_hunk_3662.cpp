     else if (ap_threads_limit < 1) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                          APLOGNO(00230) "WARNING: MaxThreads of %d not allowed, "
                          "increasing to 1.", ap_threads_limit);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02661)
                          "MaxThreads of %d not allowed, increasing to 1",
                          ap_threads_limit);
         }
         ap_threads_limit = 1;
     }
 
