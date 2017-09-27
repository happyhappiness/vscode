             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                          "RewriteOptions: MaxRedirects option has been "
                          "removed in favor of the global "
                          "LimitInternalRecursion directive and will be "
                          "ignored.");
         }
+        else if (!strcasecmp(w, "allowanyuri")) {
+            options |= OPTION_ANYURI;
+        }
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
 
 #ifndef REWRITELOG_DISABLED
