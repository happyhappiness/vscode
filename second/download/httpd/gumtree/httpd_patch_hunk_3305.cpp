     }
 
     apr_pool_clear(plog);
 
     if ( ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
-                     0, NULL, "Unable to open logs");
+                     0, NULL, APLOGNO(00015) "Unable to open logs");
         destroy_and_exit_process(process, 1);
     }
 
     if ( ap_run_post_config(pconf, plog, ptemp, ap_server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
-                     NULL, "Configuration Failed");
+                     NULL, APLOGNO(00016) "Configuration Failed");
         destroy_and_exit_process(process, 1);
     }
 
     apr_pool_destroy(ptemp);
 
     for (;;) {
+        ap_main_state = AP_SQ_MS_DESTROY_CONFIG;
         apr_hook_deregister_all();
         apr_pool_clear(pconf);
         ap_clear_auth_internal();
 
+        ap_main_state = AP_SQ_MS_CREATE_CONFIG;
+        ap_config_generation++;
         for (mod = ap_prelinked_modules; *mod != NULL; mod++) {
             ap_register_hooks(*mod, pconf);
         }
 
         /* This is a hack until we finish the code so that it only reads
          * the config file once and just operates on the tree already in
