         rv = authz_dbd_group_query(r, cfg, groups);
         if (rv != OK) {
             return AUTHZ_GENERAL_ERROR;
         }
     }
 
-    t = require_args;
+    require = ap_expr_str_exec(r, expr, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02590)
+                      "authz_dbd authorize: require dbd-group: Can't "
+                      "evaluate require expression: %s", err);
+        return AUTHZ_DENIED;
+    }
+
+    t = require;
     while (t[0]) {
         w = ap_getword_white(r->pool, &t);
         for (i=0; i < groups->nelts; ++i) {
             if (!strcmp(w, ((const char**)groups->elts)[i])) {
                 return AUTHZ_GRANTED;
             }
