  */
 static const char *mod_auth_ldap_parse_url(cmd_parms *cmd, 
                                     void *config,
                                     const char *url)
 {
     int result;
-    LDAPURLDesc *urld;
+    apr_ldap_url_desc_t *urld;
 
     mod_auth_ldap_config_t *sec = config;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
 	         cmd->server, "[%d] auth_ldap url parse: `%s'", 
 	         getpid(), url);
 
-    result = ldap_url_parse(url, &(urld));
+    result = apr_ldap_url_parse(url, &(urld));
     if (result != LDAP_SUCCESS) {
         switch (result) {
         case LDAP_URL_ERR_NOTLDAP:
             return "LDAP URL does not begin with ldap://";
         case LDAP_URL_ERR_NODN:
             return "LDAP URL does not have a DN";
