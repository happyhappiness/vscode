     apr_pool_create(&pcommands, pglobal);
     apr_pool_tag(pcommands, "pcommands");
     ap_server_pre_read_config  = apr_array_make(pcommands, 1, sizeof(char *));
     ap_server_post_read_config = apr_array_make(pcommands, 1, sizeof(char *));
     ap_server_config_defines   = apr_array_make(pcommands, 1, sizeof(char *));
 
-    ap_setup_prelinked_modules(process);
+    error = ap_setup_prelinked_modules(process);
+    if (error) {
+        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, 0, NULL, "%s: %s",
+                     ap_server_argv0, error);
+        destroy_and_exit_process(process, 1);
+    }
 
     ap_run_rewrite_args(process);
 
     /* Maintain AP_SERVER_BASEARGS list in http_main.h to allow the MPM
      * to safely pass on our args from its rewrite_args() handler.
      */
