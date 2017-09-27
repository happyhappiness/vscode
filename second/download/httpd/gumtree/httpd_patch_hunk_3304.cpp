         ap_replace_stderr_log(process->pool, temp_error_log);
     }
     ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
     if (!ap_server_conf) {
         destroy_and_exit_process(process, 1);
     }
+    apr_pool_cleanup_register(pconf, &ap_server_conf, ap_pool_cleanup_set_null,
+                              apr_pool_cleanup_null);
+    /* sort hooks here to make sure pre_config hooks are sorted properly */
+    apr_hook_sort_all();
 
     if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
-                     NULL, "Pre-configuration failed");
+                     NULL, APLOGNO(00013) "Pre-configuration failed");
         destroy_and_exit_process(process, 1);
     }
 
     rv = ap_process_config_tree(ap_server_conf, ap_conftree,
                                 process->pconf, ptemp);
     if (rv == OK) {
         ap_fixup_virtual_hosts(pconf, ap_server_conf);
         ap_fini_vhost_config(pconf, ap_server_conf);
+        /*
+         * Sort hooks again because ap_process_config_tree may have add modules
+         * and hence hooks. This happens with mod_perl and modules written in
+         * perl.
+         */
         apr_hook_sort_all();
 
         if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
-                         NULL, "Configuration check failed");
+                         NULL, APLOGNO(00014) "Configuration check failed");
             destroy_and_exit_process(process, 1);
         }
 
-        if (configtestonly) {
-            ap_run_test_config(pconf, ap_server_conf);
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
-            destroy_and_exit_process(process, 0);
-        }
-        else if (showcompile) { /* deferred due to dynamically loaded MPM */
-            show_compile_settings();
+        if (ap_run_mode != AP_SQ_RM_NORMAL) {
+            if (showcompile) { /* deferred due to dynamically loaded MPM */
+                show_compile_settings();
+            }
+            else if (showdirectives) { /* deferred in case of DSOs */
+                ap_show_directives();
+                destroy_and_exit_process(process, 0);
+            }
+            else {
+                ap_run_test_config(pconf, ap_server_conf);
+                if (ap_run_mode == AP_SQ_RM_CONFIG_TEST)
+                    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
+            }
             destroy_and_exit_process(process, 0);
         }
     }
 
     signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
     if (signal_server) {
