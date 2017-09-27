     }
 
     if (ap_threads_limit > HARD_THREAD_LIMIT) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00228)
                          "WARNING: MaxThreads of %d exceeds compile-time "
-                         "limit of", ap_threads_limit);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " %d threads, decreasing to %d.",
-                         HARD_THREAD_LIMIT, HARD_THREAD_LIMIT);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " To increase, please see the HARD_THREAD_LIMIT"
-                         "define in");
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " server/mpm/netware%s.", MPM_HARD_LIMITS_FILE);
+                         "limit of %d threads, decreasing to %d. "
+                         "To increase, please see the HARD_THREAD_LIMIT "
+                         "define in server/mpm/netware%s.",
+                         ap_threads_limit, HARD_THREAD_LIMIT, HARD_THREAD_LIMIT,
+                         MPM_HARD_LIMITS_FILE);
         } else {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00229)
                          "MaxThreads of %d exceeds compile-time limit "
                          "of %d, decreasing to match",
                          ap_threads_limit, HARD_THREAD_LIMIT);
         }
         ap_threads_limit = HARD_THREAD_LIMIT;
     }
     else if (ap_threads_limit < 1) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         APLOGNO(00230) "WARNING: MaxThreads of %d not allowed, "
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00230)
+                         "WARNING: MaxThreads of %d not allowed, "
                          "increasing to 1.", ap_threads_limit);
         } else {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02661)
                          "MaxThreads of %d not allowed, increasing to 1",
                          ap_threads_limit);
         }
