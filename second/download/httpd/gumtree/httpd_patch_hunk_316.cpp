     }
 
     apr_pool_clear(plog);
 
     if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
-                     0, NULL, "Unable to open logs\n");
+                     0, NULL, "Unable to open logs");
         destroy_and_exit_process(process, 1);
     }
 
     if ( ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
-                     NULL, "Configuration Failed\n");
+                     NULL, "Configuration Failed");
         destroy_and_exit_process(process, 1);
     }
 
     apr_pool_destroy(ptemp);
 
     for (;;) {
