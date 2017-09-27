      */
     if (!retained->first_server_limit) {
         retained->first_server_limit = server_limit;
     }
     else if (server_limit != retained->first_server_limit) {
         /* don't need a startup console version here */
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00501)
                      "changing ServerLimit to %d from original value of %d "
                      "not allowed during restart",
                      server_limit, retained->first_server_limit);
         server_limit = retained->first_server_limit;
     }
 
     if (thread_limit > MAX_THREAD_LIMIT) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00502)
                          "WARNING: ThreadLimit of %d exceeds compile-time "
                          "limit of", thread_limit);
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                          " %d threads, decreasing to %d.",
                          MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00503)
                          "ThreadLimit of %d exceeds compile-time limit "
                          "of %d, decreasing to match",
                          thread_limit, MAX_THREAD_LIMIT);
         }
         thread_limit = MAX_THREAD_LIMIT;
     }
     else if (thread_limit < 1) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00504)
                          "WARNING: ThreadLimit of %d not allowed, "
                          "increasing to 1.", thread_limit);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00505)
                          "ThreadLimit of %d not allowed, increasing to 1",
                          thread_limit);
         }
         thread_limit = 1;
     }
 
