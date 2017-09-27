         }
         else {
             cur = atol(str);
         }
     }
     else {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, APLOGNO(02173)
                      "Invalid parameters for %s", cmd->cmd->name);
         return;
     }
 
     if (arg2 && (str = ap_getword_conf(cmd->pool, &arg2))) {
         max = atol(str);
     }
 
     /* if we aren't running as root, cannot increase max */
     if (geteuid()) {
         limit->rlim_cur = cur;
-        if (max) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
+        if (max && (max > limit->rlim_max)) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, APLOGNO(02174)
                          "Must be uid 0 to raise maximum %s", cmd->cmd->name);
         }
+        else if (max) {
+            limit->rlim_max = max;
+        }
     }
     else {
         if (cur) {
             limit->rlim_cur = cur;
         }
         if (max) {
             limit->rlim_max = max;
         }
     }
 #else
 
-    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, APLOGNO(02175)
                  "Platform does not support rlimit for %s", cmd->cmd->name);
 #endif
 }
 
 APR_HOOK_STRUCT(
                APR_HOOK_LINK(get_suexec_identity)
