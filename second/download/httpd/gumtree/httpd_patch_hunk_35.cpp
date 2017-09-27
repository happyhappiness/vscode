             destroy_and_exit_process(process, exit_status);
         }
     }
 
     apr_pool_clear(plog);
 
-    /* It is assumed that if you are going to fail the open_logs phase, then
-     * you will print out your own message that explains what has gone wrong.
-     * The server doesn't need to do that for you.
-     */
     if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
+        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
+                     0, NULL, "Unable to open logs\n");
         destroy_and_exit_process(process, 1);
     }
 
     if ( ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                      NULL, "Configuration Failed\n");
