                                               const char *mode)
 {
     util_ldap_state_t *st =
     (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                               &ldap_module);
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01307)
                       "LDAP: SSL trusted mode - %s",
                        mode);
 
     if (0 == strcasecmp("NONE", mode)) {
         st->secure = APR_LDAP_NONE;
     }
