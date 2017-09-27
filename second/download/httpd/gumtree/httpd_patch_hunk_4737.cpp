     if (!data) {
         procnew = apr_pcalloc(main_server->process->pool, sizeof(*procnew));
         procnew->pid = -1;
         procnew->err = procnew->in = procnew->out = NULL;
         apr_pool_userdata_set((const void *)procnew, userdata_key,
                      apr_pool_cleanup_null, main_server->process->pool);
+        return ret;
     }
     else {
         procnew = data;
     }
 
     if (ap_state_query(AP_SQ_MAIN_STATE) != AP_SQ_MS_CREATE_PRE_CONFIG) {
         char *tmp_sockname;
         total_modules = 0;
         for (m = ap_preloaded_modules; *m != NULL; m++)
             total_modules++;
 
         parent_pid = getpid();
-        tmp_sockname = ap_server_root_relative(p, sockname);
+        tmp_sockname = ap_runtime_dir_relative(p, sockname);
         if (strlen(tmp_sockname) > sizeof(server_addr->sun_path) - 1) {
             tmp_sockname[sizeof(server_addr->sun_path)] = '\0';
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, main_server, APLOGNO(01254)
                         "The length of the ScriptSock path exceeds maximum, "
                         "truncating to %s", tmp_sockname);
         }
