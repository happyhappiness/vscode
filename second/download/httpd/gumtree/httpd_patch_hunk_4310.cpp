     const fnames *f1 = fn1;
     const fnames *f2 = fn2;
 
     return strcmp(f1->fname,f2->fname);
 }
 
+/**
+ * Used by -D DUMP_INCLUDES to output the config file "tree".
+ */
+static void dump_config_name(const char *fname, apr_pool_t *p)
+{
+    unsigned i, recursion, line_number;
+    void *data;
+    apr_file_t *out = NULL;
+
+    apr_file_open_stdout(&out, p);
+
+    /* ap_include_sentinel is defined by the core Include directive; use it to
+     * figure out how deep in the stack we are.
+     */
+    apr_pool_userdata_get(&data, "ap_include_sentinel", p);
+
+    if (data) {
+        recursion = *(unsigned *)data;
+    } else {
+        recursion = 0;
+    }
+
+    /* Indent once for each level. */
+    for (i = 0; i < (recursion + 1); ++i) {
+        apr_file_printf(out, "  ");
+    }
+
+    /* ap_include_lineno is similarly defined to tell us where in the last
+     * config file we were.
+     */
+    apr_pool_userdata_get(&data, "ap_include_lineno", p);
+
+    if (data) {
+        line_number = *(unsigned *)data;
+    } else {
+        line_number = 0;
+    }
+
+    /* Print the line number and the name of the parsed file. */
+    if (line_number > 0) {
+        apr_file_printf(out, "(%u)", line_number);
+    } else {
+        apr_file_printf(out, "(*)");
+    }
+
+    apr_file_printf(out, " %s\n", fname);
+}
+
 AP_DECLARE(const char *) ap_process_resource_config(server_rec *s,
                                                     const char *fname,
                                                     ap_directive_t **conftree,
                                                     apr_pool_t *p,
                                                     apr_pool_t *ptemp)
 {
