         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01702)
                       "auth_ldap authorize: require user: user's DN has not "
                       "been defined; failing authorization");
         return AUTHZ_DENIED;
     }
 
+    require = ap_expr_str_exec(r, expr, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02585)
+                      "auth_ldap authorize: require user: Can't evaluate expression: %s",
+                      err);
+        return AUTHZ_DENIED;
+    }
+
     /*
      * First do a whole-line compare, in case it's something like
      *   require user Babs Jensen
      */
-    result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, require_args);
+    result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, require);
     switch(result) {
         case LDAP_COMPARE_TRUE: {
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01703)
                           "auth_ldap authorize: require user: authorization "
                           "successful");
             set_request_vars(r, LDAP_AUTHZ);
