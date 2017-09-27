     }
 
     if (ap_threads_per_child > thread_limit) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00444)
                          "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
-                         "of", ap_threads_per_child);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " %d threads, decreasing to %d.",
-                         thread_limit, thread_limit);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " To increase, please see the ThreadLimit "
-                         "directive.");
+                         "of %d threads, decreasing to %d. To increase, please "
+                         "see the ThreadLimit directive.",
+                         ap_threads_per_child, thread_limit, thread_limit);
         } else if (is_parent) {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00445)
                          "ThreadsPerChild of %d exceeds ThreadLimit "
                          "of %d, decreasing to match",
                          ap_threads_per_child, thread_limit);
         }
