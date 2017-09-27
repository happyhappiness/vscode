         apr_pool_create(&ptemp, pconf);
         apr_pool_tag(ptemp, "ptemp");
         ap_server_root = def_server_root;
         server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
         if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
-                         0, NULL, "Pre-configuration failed\n");
+                         0, NULL, "Pre-configuration failed");
             destroy_and_exit_process(process, 1);
         }
 
         ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
         ap_fixup_virtual_hosts(pconf, server_conf);
         ap_fini_vhost_config(pconf, server_conf);
         apr_hook_sort_all();
         apr_pool_clear(plog);
         if (ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
-                         0, NULL, "Unable to open logs\n");
+                         0, NULL, "Unable to open logs");
             destroy_and_exit_process(process, 1);
         }
 
         if (ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
-                         0, NULL, "Configuration Failed\n");
+                         0, NULL, "Configuration Failed");
             destroy_and_exit_process(process, 1);
         }
 
         apr_pool_destroy(ptemp);
         apr_pool_lock(pconf, 1);
 
