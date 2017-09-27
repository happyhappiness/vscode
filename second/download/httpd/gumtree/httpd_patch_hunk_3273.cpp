 AP_DECLARE(int) ap_sys_privileges_handlers(int inc)
 {
     sys_privileges += inc;
     return sys_privileges;
 }
 
+static int check_errorlog_dir(apr_pool_t *p, server_rec *s)
+{
+    if (!s->error_fname || s->error_fname[0] == '|'
+        || strcmp(s->error_fname, "syslog") == 0) {
+        return APR_SUCCESS;
+    }
+    else {
+        char *abs = ap_server_root_relative(p, s->error_fname);
+        char *dir = ap_make_dirstr_parent(p, abs);
+        apr_finfo_t finfo;
+        apr_status_t rv = apr_stat(&finfo, dir, APR_FINFO_TYPE, p);
+        if (rv == APR_SUCCESS && finfo.filetype != APR_DIR)
+            rv = APR_ENOTDIR;
+        if (rv != APR_SUCCESS) {
+            const char *desc = "main error log";
+            if (s->defn_name)
+                desc = apr_psprintf(p, "error log of vhost defined at %s:%d",
+                                    s->defn_name, s->defn_line_number);
+            ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, rv,
+                          ap_server_conf, APLOGNO(02291)
+                         "Cannot access directory '%s' for %s", dir, desc);
+            return !OK;
+        }
+    }
+    return OK;
+}
+
+static int core_check_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
+{
+    int rv = OK;
+    while (s) {
+        if (check_errorlog_dir(ptemp, s) != OK)
+            rv = !OK;
+        s = s->next;
+    }
+    return rv;
+}
+
+
 static int core_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
 {
     ap_mutex_init(pconf);
-    return APR_SUCCESS;
+
+    if (!saved_server_config_defines)
+        init_config_defines(pconf);
+    apr_pool_cleanup_register(pconf, NULL, reset_config_defines,
+                              apr_pool_cleanup_null);
+
+    mpm_common_pre_config(pconf);
+
+    return OK;
 }
 
 static int core_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
 {
     ap__logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);
     ident_lookup = APR_RETRIEVE_OPTIONAL_FN(ap_ident_lookup);
