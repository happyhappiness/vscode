     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
     min_spare_threads = atoi(arg);
-    if (min_spare_threads <= 0) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: detected MinSpareThreads set to non-positive.");
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "Resetting to 1 to avoid almost certain Apache failure.");
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "Please read the documentation.");
-       min_spare_threads = 1;
-    }
-
     return NULL;
 }
 
 static const char *set_max_spare_threads(cmd_parms *cmd, void *dummy,
                                          const char *arg)
 {
