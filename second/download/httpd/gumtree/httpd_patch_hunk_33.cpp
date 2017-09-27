     else {
         fname = ap_server_root_relative(p, s->error_fname);
         if (!fname) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP, APR_EBADPATH, NULL,
                          "%s: Invalid error log path %s.",
                          ap_server_argv0, s->error_fname);
-            exit(1);
+            return DONE;
         }
         if ((rc = apr_file_open(&s->error_log, fname,
                                APR_APPEND | APR_READ | APR_WRITE | APR_CREATE,
                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                          "%s: could not open error log file %s.",
                          ap_server_argv0, fname);
-            exit(1);
+            return DONE;
         }
 
         apr_file_inherit_set(s->error_log);
     }
+
+    return OK;
 }
 
-void ap_open_logs(server_rec *s_main, apr_pool_t *p)
+int ap_open_logs(apr_pool_t *pconf, apr_pool_t *p /* plog */, 
+                 apr_pool_t *ptemp, server_rec *s_main)
 {
     apr_status_t rc = APR_SUCCESS;
     server_rec *virt, *q;
     int replace_stderr;
     apr_file_t *errfile = NULL;
 
-    open_error_log(s_main, p);
+    if (open_error_log(s_main, p) != OK) {
+        return DONE;
+    }
 
     replace_stderr = 1;
     if (s_main->error_log) {
         /* replace stderr with this new log */
         apr_file_flush(s_main->error_log);
         if ((rc = apr_file_open_stderr(&errfile, p)) == APR_SUCCESS) {
