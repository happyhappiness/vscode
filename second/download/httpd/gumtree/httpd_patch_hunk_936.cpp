 
 static int reclaim_one_pid(pid_t pid, action_t action)
 {
     apr_proc_t proc;
     apr_status_t waitret;
 
-    /* Ensure pid sanity. */
-    if (pid < 1) {
-        return 1;
-    }        
-
     proc.pid = pid;
     waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
     if (waitret != APR_CHILD_NOTDONE) {
         return 1;
     }
 
     switch(action) {
     case DO_NOTHING:
         break;
-        
+
     case SEND_SIGTERM:
         /* ok, now it's being annoying */
         ap_log_error(APLOG_MARK, APLOG_WARNING,
                      0, ap_server_conf,
                      "child process %" APR_PID_T_FMT
                      " still did not exit, "
                      "sending a SIGTERM",
                      pid);
         kill(pid, SIGTERM);
         break;
-        
+
     case SEND_SIGKILL:
         ap_log_error(APLOG_MARK, APLOG_ERR,
                      0, ap_server_conf,
                      "child process %" APR_PID_T_FMT
                      " still did not exit, "
                      "sending a SIGKILL",
