     apr_file_t *dummy = NULL;
     int rc;
 
     rc = log_child(p, program, &dummy, cmdtype, 0);
     if (rc != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
-                     "Couldn't start piped log process");
+                     "Couldn't start piped log process '%s'.",
+                     (program == NULL) ? "NULL" : program);
         return NULL;
     }
 
     pl = apr_palloc(p, sizeof (*pl));
     pl->p = p;
-    ap_piped_log_read_fd(pl) = NULL;
-    ap_piped_log_write_fd(pl) = dummy;
+    pl->read_fd = NULL;
+    pl->write_fd = dummy;
     apr_pool_cleanup_register(p, pl, piped_log_cleanup, piped_log_cleanup);
 
     return pl;
 }
 
 #endif
 
 AP_DECLARE(piped_log *) ap_open_piped_log(apr_pool_t *p,
                                           const char *program)
 {
-    apr_cmdtype_e cmdtype = APR_SHELLCMD_ENV;
+    apr_cmdtype_e cmdtype = APR_PROGRAM_ENV;
 
     /* In 2.4 favor PROGRAM_ENV, accept "||prog" syntax for compatibility
      * and "|$cmd" to override the default.
      * Any 2.2 backport would continue to favor SHELLCMD_ENV so there 
      * accept "||prog" to override, and "|$cmd" to ease conversion.
      */
-    if (*program == '|') {
-        cmdtype = APR_PROGRAM_ENV;
+    if (*program == '|')
         ++program;
-    }
-    if (*program == '$')
+    if (*program == '$') {
+        cmdtype = APR_SHELLCMD_ENV;
         ++program;
+    }
 
     return ap_open_piped_log_ex(p, program, cmdtype);
 }
 
 AP_DECLARE(void) ap_close_piped_log(piped_log *pl)
 {
     apr_pool_cleanup_run(pl->p, pl, piped_log_cleanup);
 }
 
+AP_DECLARE(const char *) ap_parse_log_level(const char *str, int *val)
+{
+    char *err = "Log level keyword must be one of emerg/alert/crit/error/warn/"
+                "notice/info/debug/trace1/.../trace8";
+    int i = 0;
+
+    if (str == NULL)
+        return err;
+
+    while (priorities[i].t_name != NULL) {
+        if (!strcasecmp(str, priorities[i].t_name)) {
+            *val = priorities[i].t_val;
+            return NULL;
+        }
+        i++;
+    }
+    return err;
+}
+
 AP_IMPLEMENT_HOOK_VOID(error_log,
-                       (const char *file, int line, int level,
+                       (const char *file, int line, int module_index, int level,
                         apr_status_t status, const server_rec *s,
                         const request_rec *r, apr_pool_t *pool,
-                        const char *errstr), (file, line, level,
+                        const char *errstr), (file, line, module_index, level,
                         status, s, r, pool, errstr))
-
