 
         cert->path = ap_server_root_relative(cmd->pool, file);
         if (cert->path &&
             ((rv = apr_stat (&finfo, cert->path, APR_FINFO_MIN, cmd->pool))
                 != APR_SUCCESS))
         {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server,
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server, APLOGNO(01306)
                          "LDAP: Could not open SSL client certificate "
                          "file - %s",
                          cert->path == NULL ? file : cert->path);
             return "Invalid client certificate file path";
         }
 
