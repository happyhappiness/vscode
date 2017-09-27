     case DO_NOTHING:
         break;
 
     case SEND_SIGTERM:
         /* ok, now it's being annoying */
         ap_log_error(APLOG_MARK, APLOG_WARNING,
-                     0, ap_server_conf,
+                     0, ap_server_conf, APLOGNO(00045)
                      "child process %" APR_PID_T_FMT
                      " still did not exit, "
                      "sending a SIGTERM",
                      pid);
         kill(pid, SIGTERM);
         break;
 
     case SEND_SIGKILL:
         ap_log_error(APLOG_MARK, APLOG_ERR,
-                     0, ap_server_conf,
+                     0, ap_server_conf, APLOGNO(00046)
                      "child process %" APR_PID_T_FMT
                      " still did not exit, "
                      "sending a SIGKILL",
                      pid);
         kill(pid, SIGKILL);
         break;
