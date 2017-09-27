             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                          "RewriteOptions: MaxRedirects option has been "
                          "removed in favor of the global "
                          "LimitInternalRecursion directive and will be "
                          "ignored.");
         }
-        else if (!strcasecmp(w, "allowanyuri")) {
-            options |= OPTION_ANYURI;
-        }
-        else if (!strcasecmp(w, "mergebase")) {
-            options |= OPTION_MERGEBASE;
-        }
         else {
             return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                                w, "'", NULL);
         }
     }
 
-    /* server command? set both global scope and base directory scope */
+    /* put it into the appropriate config */
     if (cmd->path == NULL) { /* is server command */
-        rewrite_perdir_conf *dconf = in_dconf;
-        rewrite_server_conf *sconf =
+        rewrite_server_conf *conf =
             ap_get_module_config(cmd->server->module_config,
                                  &rewrite_module);
 
-        sconf->options |= options;
-        sconf->options_set = 1;
-        dconf->options |= options;
-        dconf->options_set = 1;
+        conf->options |= options;
     }
-    /* directory command? set directory scope only */
     else {                  /* is per-directory command */
-        rewrite_perdir_conf *dconf = in_dconf;
+        rewrite_perdir_conf *conf = in_dconf;
 
-        dconf->options |= options;
-        dconf->options_set = 1;
+        conf->options |= options;
     }
 
     return NULL;
 }
 
-#ifndef REWRITELOG_DISABLED
-static const char *cmd_rewritelog(cmd_parms *cmd, void *dconf, const char *a1)
-{
-    rewrite_server_conf *sconf;
-
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
-    sconf->rewritelogfile = a1;
-
-    return NULL;
-}
-
-static const char *cmd_rewriteloglevel(cmd_parms *cmd, void *dconf,
-                                       const char *a1)
-{
-    rewrite_server_conf *sconf;
-
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
-    sconf->rewriteloglevel = atoi(a1);
-
-    return NULL;
-}
-#endif /* rewritelog */
-
 static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
                                   const char *a2)
 {
     rewrite_server_conf *sconf;
     rewritemap_entry *newmap;
     apr_finfo_t st;
