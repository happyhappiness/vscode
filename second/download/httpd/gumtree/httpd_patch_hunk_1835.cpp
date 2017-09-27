     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
     ap_threads_min_free = atoi(arg);
-    if (ap_threads_min_free <= 0) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: detected MinSpareServers set to non-positive.");
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "Resetting to 1 to avoid almost certain Apache failure.");
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "Please read the documentation.");
-       ap_threads_min_free = 1;
-    }
-
     return NULL;
 }
 
 static const char *set_max_free_threads(cmd_parms *cmd, void *dummy, const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
