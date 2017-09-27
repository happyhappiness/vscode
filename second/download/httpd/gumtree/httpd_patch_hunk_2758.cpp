         if (r->args && 0 == strcasecmp(r->args, "config")) {
             ap_rputs("<dl><dt><strong>Configuration:</strong>\n", r);
             mod_info_module_cmds(r, NULL, ap_conftree, 0, 0);
             ap_rputs("</dl><hr />", r);
         }
         else {
-            for (modp = ap_top_module; modp; modp = modp->next) {
+            int comma = 0;
+            if (!modules)
+                 modules = get_sorted_modules(r->pool);
+            for (i = 0; i < modules->nelts; i++) {
+                modp = APR_ARRAY_IDX(modules, i, module *);
                 if (!r->args || !strcasecmp(modp->name, r->args)) {
                     ap_rprintf(r,
                                "<dl><dt><a name=\"%s\"><strong>Module Name:</strong></a> "
                                "<font size=\"+1\"><tt><a href=\"?%s\">%s</a></tt></font></dt>\n",
                                modp->name, modp->name, modp->name);
                     ap_rputs("<dt><strong>Content handlers:</strong> ", r);
