     else {
         procnew = data;
     }
 
     if (ap_state_query(AP_SQ_MAIN_STATE) != AP_SQ_MS_CREATE_PRE_CONFIG) {
         char *tmp_sockname;
-        total_modules = 0;
-        for (m = ap_preloaded_modules; *m != NULL; m++)
-            total_modules++;
 
         parent_pid = getpid();
         tmp_sockname = ap_runtime_dir_relative(p, sockname);
         if (strlen(tmp_sockname) > sizeof(server_addr->sun_path) - 1) {
             tmp_sockname[sizeof(server_addr->sun_path)] = '\0';
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, main_server, APLOGNO(01254)
