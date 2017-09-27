      */
 
     ap_server_root = def_server_root;
     if (temp_error_log) {
         ap_replace_stderr_log(process->pool, temp_error_log);
     }
-    server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
-    if (!server_conf) {
+    ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
+    if (!ap_server_conf) {
         destroy_and_exit_process(process, 1);
     }
-    /* sort hooks here to make sure pre_config hooks are sorted properly */
-    apr_hook_sort_all();
 
     if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                      NULL, "Pre-configuration failed");
         destroy_and_exit_process(process, 1);
     }
 
-    rv = ap_process_config_tree(server_conf, ap_conftree,
+    rv = ap_process_config_tree(ap_server_conf, ap_conftree,
                                 process->pconf, ptemp);
     if (rv == OK) {
-        ap_fixup_virtual_hosts(pconf, server_conf);
-        ap_fini_vhost_config(pconf, server_conf);
-        /*
-         * Sort hooks again because ap_process_config_tree may have added
-         * modules and hence hooks. This happens with mod_perl and modules
-         * written in perl.
-         */
+        ap_fixup_virtual_hosts(pconf, ap_server_conf);
+        ap_fini_vhost_config(pconf, ap_server_conf);
         apr_hook_sort_all();
 
+        if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
+            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
+                         NULL, "Configuration check failed");
+            destroy_and_exit_process(process, 1);
+        }
+
         if (configtestonly) {
-            ap_run_test_config(pconf, server_conf);
+            ap_run_test_config(pconf, ap_server_conf);
             ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
             destroy_and_exit_process(process, 0);
         }
-    }
-
-    /* If our config failed, deal with that here. */
-    if (rv != OK) {
-        destroy_and_exit_process(process, 1);
+        else if (showcompile) { /* deferred due to dynamically loaded MPM */
+            show_compile_settings();
+            destroy_and_exit_process(process, 0);
+        }
     }
 
     signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
     if (signal_server) {
         int exit_status;
 
         if (signal_server(&exit_status, pconf) != 0) {
             destroy_and_exit_process(process, exit_status);
         }
     }
 
+    /* If our config failed, deal with that here. */
+    if (rv != OK) {
+        destroy_and_exit_process(process, 1);
+    }
+
     apr_pool_clear(plog);
 
-    if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
+    if ( ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                      0, NULL, "Unable to open logs");
         destroy_and_exit_process(process, 1);
     }
 
-    if ( ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
+    if ( ap_run_post_config(pconf, plog, ptemp, ap_server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                      NULL, "Configuration Failed");
         destroy_and_exit_process(process, 1);
     }
 
     apr_pool_destroy(ptemp);
 
     for (;;) {
         apr_hook_deregister_all();
         apr_pool_clear(pconf);
+        ap_clear_auth_internal();
 
         for (mod = ap_prelinked_modules; *mod != NULL; mod++) {
             ap_register_hooks(*mod, pconf);
         }
 
         /* This is a hack until we finish the code so that it only reads
