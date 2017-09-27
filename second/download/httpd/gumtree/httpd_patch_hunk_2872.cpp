 {
     rewrite_perdir_conf *dconf = in_dconf;
     rewrite_server_conf *sconf;
 
     sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
 
-    if (cmd->path == NULL) { /* is server command */
+    /* server command? set both global scope and base directory scope */
+    if (cmd->path == NULL) {
         sconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
+        sconf->state_set = 1;
+        dconf->state = sconf->state;
+        dconf->state_set = 1;
     }
-    else                   /* is per-directory command */ {
+    /* directory command? set directory scope only */
+    else {
         dconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
+        dconf->state_set = 1;
     }
 
     return NULL;
 }
 
 static const char *cmd_rewriteoptions(cmd_parms *cmd,
                                       void *in_dconf, const char *option)
 {
     int options = 0;
-    char *w;
 
     while (*option) {
-        w = ap_getword_conf(cmd->pool, &option);
+        char *w = ap_getword_conf(cmd->temp_pool, &option);
 
         if (!strcasecmp(w, "inherit")) {
             options |= OPTION_INHERIT;
         }
+        else if (!strcasecmp(w, "inheritbefore")) {
+            options |= OPTION_INHERIT_BEFORE;
+        }
+        else if (!strcasecmp(w, "allownoslash")) {
+            options |= OPTION_NOSLASH;
+        }
         else if (!strncasecmp(w, "MaxRedirects=", 13)) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00664)
                          "RewriteOptions: MaxRedirects option has been "
                          "removed in favor of the global "
                          "LimitInternalRecursion directive and will be "
                          "ignored.");
         }
         else {
             return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                                w, "'", NULL);
         }
     }
 
-    /* put it into the appropriate config */
+    /* server command? set both global scope and base directory scope */
     if (cmd->path == NULL) { /* is server command */
-        rewrite_server_conf *conf =
+        rewrite_perdir_conf *dconf = in_dconf;
+        rewrite_server_conf *sconf =
             ap_get_module_config(cmd->server->module_config,
                                  &rewrite_module);
 
-        conf->options |= options;
+        sconf->options |= options;
+        sconf->options_set = 1;
+        dconf->options |= options;
+        dconf->options_set = 1;
     }
+    /* directory command? set directory scope only */
     else {                  /* is per-directory command */
-        rewrite_perdir_conf *conf = in_dconf;
+        rewrite_perdir_conf *dconf = in_dconf;
 
-        conf->options |= options;
+        dconf->options |= options;
+        dconf->options_set = 1;
     }
 
     return NULL;
 }
 
 static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
