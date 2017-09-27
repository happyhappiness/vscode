 
     /* add environment variables */
     remote_user_attribute_set = set_request_vars(r, LDAP_AUTHN);
 
     /* sanity check */
     if (sec->remote_user_attribute && !remote_user_attribute_set) {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01696)
                   "auth_ldap authenticate: "
                   "REMOTE_USER was to be set with attribute '%s', "
                   "but this attribute was not requested for in the "
                   "LDAP query for the user. REMOTE_USER will fall "
                   "back to username or DN as appropriate.",
                   sec->remote_user_attribute);
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01697)
                   "auth_ldap authenticate: accepting %s", user);
 
     return AUTH_GRANTED;
 }
 
 static authz_status ldapuser_check_authorization(request_rec *r,
-                                             const char *require_args)
+                                                 const char *require_args,
+                                                 const void *parsed_require_args)
 {
     int result = 0;
     authn_ldap_request_t *req =
         (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
     authn_ldap_config_t *sec =
         (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
