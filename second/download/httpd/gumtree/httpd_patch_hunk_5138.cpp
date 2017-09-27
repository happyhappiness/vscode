         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01742)
                       "auth_ldap authorize: require ldap-filter: user's DN "
                       "has not been defined; failing authorization");
         return AUTHZ_DENIED;
     }
 
-    t = require_args;
+    require = ap_expr_str_exec(r, expr, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02589)
+                      "auth_ldap authorize: require ldap-filter: Can't "
+                      "evaluate require expression: %s", err);
+        return AUTHZ_DENIED;
+    }
+
+    t = require;
 
     if (t[0]) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01743)
                       "auth_ldap authorize: checking filter %s", t);
 
         /* Build the username filter */
