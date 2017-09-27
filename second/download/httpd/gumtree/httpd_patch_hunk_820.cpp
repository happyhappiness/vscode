     if (!filename) {
         return;
     }
 
     fname = ap_server_root_relative(p, filename);
     if (!fname) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH, 
+        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH,
                      NULL, "Invalid PID file path %s, ignoring.", filename);
         return;
     }
 
     mypid = getpid();
     if (mypid != saved_pid
