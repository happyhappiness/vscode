 }
 
 static void put_int_flush_right(request_rec * r, int i, int field)
 {
     if (field > 1 || i > 9)
         put_int_flush_right(r, i / 10, field - 1);
-    if (i)
-        ap_rputc('0' + i % 10, r);
+    if (i) {
+        if (r)
+            ap_rputc('0' + i % 10, r);
+        else
+            apr_file_putc('0' + i % 10, out);
+    }
+    else {
+        if (r)
+            ap_rputs("&nbsp;", r);
+        else
+            apr_file_printf(out, " ");
+    }
+}
+
+static void set_fn_info(request_rec *r, const char *name)
+{
+    if (r)
+        ap_set_module_config(r->request_config, &info_module, (void *)name);
+    else
+        dump_config_fn_info = name;
+}
+
+static const char *get_fn_info(request_rec *r)
+{
+    if (r)
+        return ap_get_module_config(r->request_config, &info_module);
     else
-        ap_rputs("&nbsp;", r);
+        return dump_config_fn_info;
 }
 
+
 static void mod_info_indent(request_rec * r, int nest,
                             const char *thisfn, int linenum)
 {
     int i;
-    const char *prevfn =
-        ap_get_module_config(r->request_config, &info_module);
+    const char *prevfn = get_fn_info(r);
     if (thisfn == NULL)
         thisfn = "*UNKNOWN*";
     if (prevfn == NULL || 0 != strcmp(prevfn, thisfn)) {
-        thisfn = ap_escape_html(r->pool, thisfn);
-        ap_rprintf(r, "<dd><tt><strong>In file: %s</strong></tt></dd>\n",
+        if (r) {
+            thisfn = ap_escape_html(r->pool, thisfn);
+            ap_rprintf(r, "<dd><tt><strong>In file: %s</strong></tt></dd>\n",
                    thisfn);
-        ap_set_module_config(r->request_config, &info_module,
-                             (void *) thisfn);
+        }
+        else {
+            apr_file_printf(out, "# In file: %s\n", thisfn);
+        }
+        set_fn_info(r, thisfn);
     }
 
-    ap_rputs("<dd><tt>", r);
-    put_int_flush_right(r, linenum > 0 ? linenum : 0, 4);
-    ap_rputs(":&nbsp;", r);
+    if (r) {
+        ap_rputs("<dd><tt>", r);
+        put_int_flush_right(r, linenum > 0 ? linenum : 0, 4);
+        ap_rputs(":&nbsp;", r);
+    }
+    else if (linenum > 0) {
+        for (i = 1; i <= nest; ++i)
+            apr_file_printf(out, "  ");
+        apr_file_putc('#', out);
+        put_int_flush_right(r, linenum, 4);
+        apr_file_printf(out, ":\n");
+    }
 
     for (i = 1; i <= nest; ++i) {
-        ap_rputs("&nbsp;&nbsp;", r);
+        if (r)
+            ap_rputs("&nbsp;&nbsp;", r);
+        else
+            apr_file_printf(out, "  ");
     }
 }
 
 static void mod_info_show_cmd(request_rec * r, const ap_directive_t * dir,
                               int nest)
 {
     mod_info_indent(r, nest, dir->filename, dir->line_num);
-    ap_rprintf(r, "%s <i>%s</i></tt></dd>\n",
-               ap_escape_html(r->pool, dir->directive),
-               ap_escape_html(r->pool, dir->args));
+    if (r)
+        ap_rprintf(r, "%s <i>%s</i></tt></dd>\n",
+                   ap_escape_html(r->pool, dir->directive),
+                   ap_escape_html(r->pool, dir->args));
+    else
+        apr_file_printf(out, "%s %s\n", dir->directive, dir->args);
 }
 
 static void mod_info_show_open(request_rec * r, const ap_directive_t * dir,
                                int nest)
 {
     mod_info_indent(r, nest, dir->filename, dir->line_num);
-    ap_rprintf(r, "%s %s</tt></dd>\n",
-               ap_escape_html(r->pool, dir->directive),
-               ap_escape_html(r->pool, dir->args));
+    if (r)
+        ap_rprintf(r, "%s %s</tt></dd>\n",
+                   ap_escape_html(r->pool, dir->directive),
+                   ap_escape_html(r->pool, dir->args));
+    else
+        apr_file_printf(out, "%s %s\n", dir->directive, dir->args);
 }
 
 static void mod_info_show_close(request_rec * r, const ap_directive_t * dir,
                                 int nest)
 {
     const char *dirname = dir->directive;
     mod_info_indent(r, nest, dir->filename, 0);
     if (*dirname == '<') {
-        ap_rprintf(r, "&lt;/%s&gt;</tt></dd>",
-                   ap_escape_html(r->pool, dirname + 1));
+        if (r)
+            ap_rprintf(r, "&lt;/%s&gt;</tt></dd>",
+                       ap_escape_html(r->pool, dirname + 1));
+        else
+            apr_file_printf(out, "</%s>\n", dirname + 1);
     }
     else {
-        ap_rprintf(r, "/%s</tt></dd>", ap_escape_html(r->pool, dirname));
+        if (r)
+            ap_rprintf(r, "/%s</tt></dd>", ap_escape_html(r->pool, dirname));
+        else
+            apr_file_printf(out, "/%s\n", dirname);
     }
 }
 
 static int mod_info_has_cmd(const command_rec * cmds, ap_directive_t * dir)
 {
     const command_rec *cmd;
