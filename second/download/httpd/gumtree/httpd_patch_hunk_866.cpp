     }
 
     ap_daemons_max_free = atoi(arg);
     return NULL;
 }
 
-static const char *set_max_clients (cmd_parms *cmd, void *dummy, const char *arg) 
+static const char *set_max_clients (cmd_parms *cmd, void *dummy, const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
     ap_daemons_limit = atoi(arg);
     if (ap_daemons_limit > server_limit) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
+       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: MaxClients of %d exceeds ServerLimit value "
                     "of %d servers,", ap_daemons_limit, server_limit);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
+       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     " lowering MaxClients to %d.  To increase, please "
                     "see the ServerLimit", server_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     " directive.");
        ap_daemons_limit = server_limit;
-    } 
+    }
     else if (ap_daemons_limit < 1) {
-	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                      "WARNING: Require MaxClients > 0, setting to 1");
 	ap_daemons_limit = 1;
     }
     return NULL;
 }
 
-static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg) 
+static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg)
 {
     int tmp_server_limit;
-    
+
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
     tmp_server_limit = atoi(arg);
