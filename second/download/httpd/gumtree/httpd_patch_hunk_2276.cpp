     }
 
     t = require_args;
 
     if (req->dn == NULL || strlen(req->dn) == 0) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "[%" APR_PID_T_FMT "] auth_ldap authorize: "
-                      "require dn: user's DN has not been defined; failing authorization",
-                      getpid());
+                      "auth_ldap authorize: require dn: user's DN has not "
+                      "been defined; failing authorization");
         return AUTHZ_DENIED;
     }
 
     result = util_ldap_cache_comparedn(r, ldc, sec->url, req->dn, t, sec->compare_dn_on_server);
     switch(result) {
         case LDAP_COMPARE_TRUE: {
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "[%" APR_PID_T_FMT "] auth_ldap authorize: "
-                          "require dn: authorization successful", getpid());
+                          "auth_ldap authorize: "
+                          "require dn: authorization successful");
             set_request_vars(r, LDAP_AUTHZ);
             return AUTHZ_GRANTED;
         }
         default: {
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                          "auth_ldap authorize: "
                           "require dn \"%s\": LDAP error [%s][%s]",
-                          getpid(), t, ldc->reason, ldap_err2string(result));
+                          t, ldc->reason, ldap_err2string(result));
         }
     }
 
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "[%" APR_PID_T_FMT "] auth_ldap authorize dn: authorization denied for user %s to %s",
-                  getpid(), r->user, r->uri);
+                  "auth_ldap authorize dn: authorization denied for "
+                  "user %s to %s",
+                  r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 static authz_status ldapattribute_check_authorization(request_rec *r,
                                              const char *require_args)
