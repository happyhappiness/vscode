     const char *err = ap_check_cmd_context(cmd,
                                            NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);
     if (err != NULL) {
         return err;
     }
 
+    /* When ap_document_root_check is false; skip all the stuff below */
+    if (!ap_document_root_check) {
+       conf->ap_document_root = arg;
+       return NULL;
+    }
+
     /* Make it absolute, relative to ServerRoot */
     arg = ap_server_root_relative(cmd->pool, arg);
     if (arg == NULL) {
         return "DocumentRoot must be a directory";
     }
 
-    /* TODO: ap_configtestonly && ap_docrootcheck && */
+    /* TODO: ap_configtestonly */
     if (apr_filepath_merge((char**)&conf->ap_document_root, NULL, arg,
                            APR_FILEPATH_TRUENAME, cmd->pool) != APR_SUCCESS
         || !ap_is_directory(cmd->pool, arg)) {
         if (cmd->server->is_virtual) {
             ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0,
                           cmd->pool,
