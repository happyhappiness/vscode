                                               &authz_dbd_module);
 
     if (!r->user) {
         return AUTHZ_DENIED_NO_USER;
     }
 
-    if (groups == NULL) {
-        groups = apr_array_make(r->pool, 4, sizeof(const char*));
-        rv = authz_dbd_group_query(r, cfg, groups);
-        if (rv != OK) {
-            return AUTHZ_GENERAL_ERROR;
-        }
+    groups = apr_array_make(r->pool, 4, sizeof(const char*));
+    rv = authz_dbd_group_query(r, cfg, groups);
+    if (rv != OK) {
+        return AUTHZ_GENERAL_ERROR;
     }
 
     require = ap_expr_str_exec(r, expr, &err);
     if (err) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02590)
                       "authz_dbd authorize: require dbd-group: Can't "
