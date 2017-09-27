     ap_server_root = def_server_root;
     if (temp_error_log) {
         ap_replace_stderr_log(process->pool, temp_error_log);
     }
     ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
     if (!ap_server_conf) {
+        if (showcompile) {
+            /* Well, we tried. Show as much as we can, but exit nonzero to
+             * indicate that something's not right. The cause should have
+             * already been logged. */
+            show_compile_settings();
+        }
         destroy_and_exit_process(process, 1);
     }
     apr_pool_cleanup_register(pconf, &ap_server_conf, ap_pool_cleanup_set_null,
                               apr_pool_cleanup_null);
+
+    if (showcompile) { /* deferred due to dynamically loaded MPM */
+        show_compile_settings();
+        destroy_and_exit_process(process, 0);
+    }
+
     /* sort hooks here to make sure pre_config hooks are sorted properly */
     apr_hook_sort_all();
 
     if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                      NULL, APLOGNO(00013) "Pre-configuration failed");
