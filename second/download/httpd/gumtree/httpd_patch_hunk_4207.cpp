     ap_log_set_writer(ap_default_log_writer);
     buffered_logs = 0;
 
     return OK;
 }
 
+static int check_log_dir(apr_pool_t *p, server_rec *s, config_log_state *cls)
+{
+    if (!cls->fname || cls->fname[0] == '|' || !cls->directive) {
+        return OK;
+    }
+    else {
+        char *abs = ap_server_root_relative(p, cls->fname);
+        char *dir = ap_make_dirstr_parent(p, abs);
+        apr_finfo_t finfo;
+        const ap_directive_t *directive = cls->directive;
+        apr_status_t rv = apr_stat(&finfo, dir, APR_FINFO_TYPE, p);
+        cls->directive = NULL; /* Don't check this config_log_state again */
+        if (rv == APR_SUCCESS && finfo.filetype != APR_DIR)
+            rv = APR_ENOTDIR;
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, rv, s,
+                         APLOGNO(02297)
+                         "Cannot access directory '%s' for log file '%s' "
+                         "defined at %s:%d", dir, cls->fname,
+                         directive->filename, directive->line_num);
+            return !OK;
+        }
+    }
+    return OK;
+}
+
+static int log_check_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
+{
+    int rv = OK;
+    while (s) {
+        multi_log_state *mls = ap_get_module_config(s->module_config,
+                                                    &log_config_module);
+        /*
+         * We don't need to check mls->server_config_logs because it just
+         * points to the parent server's mls->config_logs.
+         */
+        apr_array_header_t *log_list = mls->config_logs;
+        config_log_state *clsarray = (config_log_state *) log_list->elts;
+        int i;
+        for (i = 0; i < log_list->nelts; ++i) {
+            if (check_log_dir(ptemp, s, &clsarray[i]) != OK)
+                rv = !OK;
+        }
+
+        s = s->next;
+    }
+    return rv;
+}
+
 static void register_hooks(apr_pool_t *p)
 {
     ap_hook_pre_config(log_pre_config,NULL,NULL,APR_HOOK_REALLY_FIRST);
+    ap_hook_check_config(log_check_config,NULL,NULL,APR_HOOK_MIDDLE);
     ap_hook_child_init(init_child,NULL,NULL,APR_HOOK_MIDDLE);
     ap_hook_open_logs(init_config_log,NULL,NULL,APR_HOOK_MIDDLE);
     ap_hook_log_transaction(multi_log_transaction,NULL,NULL,APR_HOOK_MIDDLE);
 
     /* Init log_hash before we register the optional function. It is
      * possible for the optional function, ap_register_log_handler,
