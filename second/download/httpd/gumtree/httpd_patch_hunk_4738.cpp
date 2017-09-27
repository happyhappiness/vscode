 
     ap_rputs("</dl>\n<hr />\n", r);
 
     return 0;
 }
 
+static int cmp_provider_groups(const void *a_, const void *b_)
+{
+    const ap_list_provider_groups_t *a = a_, *b = b_;
+    int ret = strcmp(a->provider_group, b->provider_group);
+    if (!ret)
+        ret = strcmp(a->provider_version, b->provider_version);
+    return ret;
+}
+
+static int cmp_provider_names(const void *a_, const void *b_)
+{
+    const ap_list_provider_names_t *a = a_, *b = b_;
+    return strcmp(a->provider_name, b->provider_name);
+}
+
+static void show_providers(request_rec *r)
+{
+    apr_array_header_t *groups = ap_list_provider_groups(r->pool);
+    ap_list_provider_groups_t *group;
+    apr_array_header_t *names;
+    ap_list_provider_names_t *name;
+    int i,j;
+    const char *cur_group = NULL;
+
+    qsort(groups->elts, groups->nelts, sizeof(ap_list_provider_groups_t),
+          cmp_provider_groups);
+    ap_rputs("<h2><a name=\"providers\">Providers</a></h2>\n<dl>", r);
+
+    for (i = 0; i < groups->nelts; i++) {
+        group = &APR_ARRAY_IDX(groups, i, ap_list_provider_groups_t);
+        if (!cur_group || strcmp(cur_group, group->provider_group) != 0) {
+            if (cur_group)
+                ap_rputs("\n</dt>\n", r);
+            cur_group = group->provider_group;
+            ap_rprintf(r, "<dt><strong>%s</strong> (version <tt>%s</tt>):"
+                          "\n <br />\n", cur_group, group->provider_version);
+        }
+        names = ap_list_provider_names(r->pool, group->provider_group,
+                                       group->provider_version);
+        qsort(names->elts, names->nelts, sizeof(ap_list_provider_names_t),
+              cmp_provider_names);
+        for (j = 0; j < names->nelts; j++) {
+            name = &APR_ARRAY_IDX(names, j, ap_list_provider_names_t);
+            ap_rprintf(r, "<tt>&nbsp;&nbsp;%s</tt><br/>", name->provider_name);
+        }
+    }
+    if (cur_group)
+        ap_rputs("\n</dt>\n", r);
+    ap_rputs("</dl>\n<hr />\n", r);
+}
+
 static int cmp_module_name(const void *a_, const void *b_)
 {
     const module * const *a = a_;
     const module * const *b = b_;
     return strcmp((*a)->name, (*b)->name);
 }
