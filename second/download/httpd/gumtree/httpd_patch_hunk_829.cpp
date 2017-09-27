 
     ap_server_root = def_server_root;
     if (temp_error_log) {
         ap_replace_stderr_log(process->pool, temp_error_log);
     }
     server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
+    if (!server_conf) {
+        destroy_and_exit_process(process, 1);
+    }
+
     if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                      NULL, "Pre-configuration failed");
         destroy_and_exit_process(process, 1);
     }
 
-    ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
-    ap_fixup_virtual_hosts(pconf, server_conf);
-    ap_fini_vhost_config(pconf, server_conf);
-    apr_hook_sort_all();
-    if (configtestonly) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
-        destroy_and_exit_process(process, 0);
+    rv = ap_process_config_tree(server_conf, ap_conftree,
+                                process->pconf, ptemp);
+    if (rv == OK) {
+        ap_fixup_virtual_hosts(pconf, server_conf);
+        ap_fini_vhost_config(pconf, server_conf);
+        apr_hook_sort_all();
+
+        if (configtestonly) {
+            ap_run_test_config(pconf, server_conf);
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
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
 
     if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                      0, NULL, "Unable to open logs");
         destroy_and_exit_process(process, 1);
