          * memory.  rbb
          */
         ap_conftree = NULL;
         apr_pool_create(&ptemp, pconf);
         apr_pool_tag(ptemp, "ptemp");
         ap_server_root = def_server_root;
-        server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
-        if (!server_conf) {
+        ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
+        if (!ap_server_conf) {
             destroy_and_exit_process(process, 1);
         }
-        /* sort hooks here to make sure pre_config hooks are sorted properly */
-        apr_hook_sort_all();
 
         if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                          0, NULL, "Pre-configuration failed");
             destroy_and_exit_process(process, 1);
         }
 
-        if (ap_process_config_tree(server_conf, ap_conftree, process->pconf,
+        if (ap_process_config_tree(ap_server_conf, ap_conftree, process->pconf,
                                    ptemp) != OK) {
             destroy_and_exit_process(process, 1);
         }
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
+
+        if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
+            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
+                         NULL, "Configuration check failed");
+            destroy_and_exit_process(process, 1);
+        }
+
         apr_pool_clear(plog);
-        if (ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
+        if (ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                          0, NULL, "Unable to open logs");
             destroy_and_exit_process(process, 1);
         }
 
-        if (ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
+        if (ap_run_post_config(pconf, plog, ptemp, ap_server_conf) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                          0, NULL, "Configuration Failed");
             destroy_and_exit_process(process, 1);
         }
 
         apr_pool_destroy(ptemp);
         apr_pool_lock(pconf, 1);
 
         ap_run_optional_fn_retrieve();
 
-        if (ap_mpm_run(pconf, plog, server_conf))
+        if (ap_run_mpm(pconf, plog, ap_server_conf) != OK)
             break;
 
         apr_pool_lock(pconf, 0);
     }
 
     apr_pool_lock(pconf, 0);
