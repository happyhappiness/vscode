     for (i = 0; i < process->argc; i++) {
         strcat(result, process->argv[i]);
         if ((i+1)< process->argc) {
             strcat(result, " ");
         }
     }
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(00094)
                  "Command line: '%s'", result);
 }
 
+AP_DECLARE(void) ap_remove_pid(apr_pool_t *p, const char *rel_fname)
+{
+    apr_status_t rv;
+    const char *fname = ap_server_root_relative(p, rel_fname);
+
+    if (fname != NULL) {
+        rv = apr_file_remove(fname, p);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00095)
+                         "failed to remove PID file %s", fname);
+        }
+        else {
+            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00096)
+                         "removed PID file %s (pid=%" APR_PID_T_FMT ")",
+                         fname, getpid());
+        }
+    }
+}
+
 AP_DECLARE(void) ap_log_pid(apr_pool_t *p, const char *filename)
 {
     apr_file_t *pid_file = NULL;
     apr_finfo_t finfo;
     static pid_t saved_pid = -1;
     pid_t mypid;
