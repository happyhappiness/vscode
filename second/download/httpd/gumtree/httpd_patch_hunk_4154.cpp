     }
 
     if (max_workers < threads_per_child) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00511)
                          "WARNING: MaxRequestWorkers of %d is less than "
-                         "ThreadsPerChild of", max_workers);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " %d, increasing to %d.  MaxRequestWorkers must be at "
-                         "least as large",
-                         threads_per_child, threads_per_child);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " as the number of threads in a single server.");
+                         "ThreadsPerChild of %d, increasing to %d. "
+                         "MaxRequestWorkers must be at least as large "
+                         "as the number of threads in a single server.",
+                         max_workers, threads_per_child, threads_per_child);
         } else {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00512)
                          "MaxRequestWorkers of %d is less than ThreadsPerChild "
                          "of %d, increasing to match",
                          max_workers, threads_per_child);
         }
