             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                          NULL, APLOGNO(00014) "Configuration check failed");
             destroy_and_exit_process(process, 1);
         }
 
         if (ap_run_mode != AP_SQ_RM_NORMAL) {
-            if (showcompile) { /* deferred due to dynamically loaded MPM */
-                show_compile_settings();
-            }
-            else if (showdirectives) { /* deferred in case of DSOs */
+            if (showdirectives) { /* deferred in case of DSOs */
                 ap_show_directives();
                 destroy_and_exit_process(process, 0);
             }
             else {
                 ap_run_test_config(pconf, ap_server_conf);
                 if (ap_run_mode == AP_SQ_RM_CONFIG_TEST)
