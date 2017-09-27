                     max_clients, ap_daemons_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     " and would exceed the ServerLimit value of %d.",
                     server_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     " Automatically lowering MaxClients to %d.  To increase,",
-                    server_limit);
+                    server_limit * ap_threads_per_child);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     " please see the ServerLimit directive.");
        ap_daemons_limit = server_limit;
     } 
     else if (ap_daemons_limit < 1) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
