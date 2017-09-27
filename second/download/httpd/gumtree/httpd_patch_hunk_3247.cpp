 
 #define AP_MAX_ARGC 64
 
 static const char *invoke_cmd(const command_rec *cmd, cmd_parms *parms,
                               void *mconfig, const char *args)
 {
+    int override_list_ok = 0;
     char *w, *w2, *w3;
     const char *errmsg = NULL;
 
-    if ((parms->override & cmd->req_override) == 0)
-        return apr_pstrcat(parms->pool, cmd->name, " not allowed here", NULL);
+    /** Have we been provided a list of acceptable directives? */
+    if(parms->override_list != NULL)
+         if(apr_table_get(parms->override_list, cmd->name) != NULL)
+              override_list_ok = 1;
+
+    if ((parms->override & cmd->req_override) == 0 && !override_list_ok) {
+        if (parms->override & NONFATAL_OVERRIDE) {
+            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->temp_pool,
+                          APLOGNO(02295)
+                          "%s in .htaccess forbidden by AllowOverride",
+                          cmd->name);
+            return NULL;
+        }
+        else {
+            return apr_pstrcat(parms->pool, cmd->name,
+                               " not allowed here", NULL);
+        }
+    }
 
     parms->info = cmd->cmd_data;
     parms->cmd = cmd;
 
     switch (cmd->args_how) {
     case RAW_ARGS:
