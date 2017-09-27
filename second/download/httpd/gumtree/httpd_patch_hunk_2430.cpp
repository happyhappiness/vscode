      */
     t = require_args;
     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, w);
         switch(result) {
             case LDAP_COMPARE_TRUE: {
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01705)
                               "auth_ldap authorize: "
                               "require user: authorization successful");
                 set_request_vars(r, LDAP_AUTHZ);
                 return AUTHZ_GRANTED;
             }
             default: {
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01706)
                               "auth_ldap authorize: "
                               "require user: authorization failed [%s][%s]",
                               ldc->reason, ldap_err2string(result));
             }
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01707)
                   "auth_ldap authorize user: authorization denied for "
                   "user %s to %s",
                   r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 static authz_status ldapgroup_check_authorization(request_rec *r,
-                                             const char *require_args)
+                                                  const char *require_args,
+                                                  const void *parsed_require_args)
 {
     int result = 0;
     authn_ldap_request_t *req =
         (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
     authn_ldap_config_t *sec =
         (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
