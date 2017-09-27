         return "DocumentRoot must be a directory";
     }
 
     /* TODO: ap_configtestonly */
     if (apr_filepath_merge((char**)&conf->ap_document_root, NULL, arg,
                            APR_FILEPATH_TRUENAME, cmd->pool) != APR_SUCCESS
-        || !ap_is_directory(cmd->pool, arg)) {
+        || !ap_is_directory(cmd->temp_pool, arg)) {
         if (cmd->server->is_virtual) {
             ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0,
                           cmd->pool, APLOGNO(00112)
                           "Warning: DocumentRoot [%s] does not exist",
                           arg);
             conf->ap_document_root = arg;
