         }
 
         if (!r->args || !strcasecmp(r->args, "hooks")) {
             show_active_hooks(r);
         }
 
+        if (!r->args || !strcasecmp(r->args, "providers")) {
+            show_providers(r);
+        }
+
         if (r->args && 0 == strcasecmp(r->args, "config")) {
             ap_rputs("<dl><dt><strong>Configuration:</strong>\n", r);
             mod_info_module_cmds(r, NULL, ap_conftree, 0, 0);
             ap_rputs("</dl><hr />", r);
         }
         else {
