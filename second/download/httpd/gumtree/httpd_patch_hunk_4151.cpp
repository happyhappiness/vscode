     }
 
     if (server_limit > MAX_SERVER_LIMIT) {
         if (startup) {
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00497)
                          "WARNING: ServerLimit of %d exceeds compile-time "
-                         "limit of", server_limit);
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
-                         " %d servers, decreasing to %d.",
-                         MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);
+                         "limit of %d servers, decreasing to %d.",
+                         server_limit, MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);
         } else {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00498)
                          "ServerLimit of %d exceeds compile-time limit "
                          "of %d, decreasing to match",
                          server_limit, MAX_SERVER_LIMIT);
         }
