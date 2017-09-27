                       "Authorization of user %s to access %s failed, reason: "
                       "user doesn't appear in group file (%s).",
                       r->user, r->uri, conf->groupfile);
         return AUTHZ_DENIED;
     }
 
-    t = require_args;
+    require = ap_expr_str_exec(r, expr, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02592)
+                      "authz_groupfile authorize: require group: Can't "
+                      "evaluate require expression: %s", err);
+        return AUTHZ_DENIED;
+    }
+
+    t = require;
     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         if (apr_table_get(grpstatus, w)) {
             return AUTHZ_GRANTED;
         }
     }
 
