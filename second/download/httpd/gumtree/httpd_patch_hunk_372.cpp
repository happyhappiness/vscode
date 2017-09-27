 
 static const char *util_ldap_set_cert_auth(cmd_parms *cmd, void *dummy, const char *file)
 {
     util_ldap_state_t *st = 
         (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
 						  &ldap_module);
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err != NULL) {
+        return err;
+    }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                       "LDAP: SSL trusted certificate authority file - %s", 
                        file);
 
-    st->cert_auth_file = apr_pstrdup(cmd->pool, file);
+    st->cert_auth_file = ap_server_root_relative(cmd->pool, file);
 
     return(NULL);
 }
 
 
 const char *util_ldap_set_cert_type(cmd_parms *cmd, void *dummy, const char *Type)
 {
     util_ldap_state_t *st = 
     (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
                                               &ldap_module);
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err != NULL) {
+        return err;
+    }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                       "LDAP: SSL trusted certificate authority file type - %s", 
                        Type);
 
     if (0 == strcmp("DER_FILE", Type))
