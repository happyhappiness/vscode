     t = require_args;
     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, w);
         switch(result) {
             case LDAP_COMPARE_TRUE: {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                              "[%" APR_PID_T_FMT "] auth_ldap authorize: "
-                              "require user: authorization successful", getpid());
+                              "auth_ldap authorize: "
+                              "require user: authorization successful");
                 set_request_vars(r, LDAP_AUTHZ);
                 return AUTHZ_GRANTED;
             }
             default: {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                              "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                              "auth_ldap authorize: "
                               "require user: authorization failed [%s][%s]",
-                              getpid(), ldc->reason, ldap_err2string(result));
+                              ldc->reason, ldap_err2string(result));
             }
         }
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "[%" APR_PID_T_FMT "] auth_ldap authorize user: authorization denied for user %s to %s",
-                  getpid(), r->user, r->uri);
+                  "auth_ldap authorize user: authorization denied for "
+                  "user %s to %s",
+                  r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 static authz_status ldapgroup_check_authorization(request_rec *r,
                                              const char *require_args)
