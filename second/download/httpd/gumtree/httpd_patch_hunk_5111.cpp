     {
         /* The child process or in one_process (debug) mode
          */
         ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00453)
                      "Child process is running");
 
-        child_main(pconf);
+        child_main(pconf, parent_pid);
 
         ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00454)
                      "Child process is exiting");
         return DONE;
     }
     else
