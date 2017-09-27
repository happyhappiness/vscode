 static const char *util_ldap_set_cert_auth(cmd_parms *cmd, void *dummy, const char *file)
 {
     util_ldap_state_t *st = 
         (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
 						  &ldap_module);
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    apr_finfo_t finfo;
+    apr_status_t rv;
+
     if (err != NULL) {
         return err;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                       "LDAP: SSL trusted certificate authority file - %s", 
                        file);
 
     st->cert_auth_file = ap_server_root_relative(cmd->pool, file);
 
+    if (st->cert_auth_file && 
+        ((rv = apr_stat (&finfo, st->cert_auth_file, APR_FINFO_MIN, cmd->pool)) != APR_SUCCESS))
+    {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server, 
+                     "LDAP: Could not open SSL trusted certificate authority file - %s", 
+                     st->cert_auth_file == NULL ? file : st->cert_auth_file);
+        return "Invalid file path";
+    }
+
     return(NULL);
 }
 
 
-const char *util_ldap_set_cert_type(cmd_parms *cmd, void *dummy, const char *Type)
+static const char *util_ldap_set_cert_type(cmd_parms *cmd, void *dummy, const char *Type)
 {
     util_ldap_state_t *st = 
     (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
                                               &ldap_module);
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
