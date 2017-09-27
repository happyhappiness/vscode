                             const char *description)
 {
     ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL,
                  "%s", description);
 }
 
+/* Create a child process running PROGNAME with a pipe connected to
+ * the childs stdin.  The write-end of the pipe will be placed in
+ * *FPIN on successful return.  If dummy_stderr is non-zero, the
+ * stderr for the child will be the same as the stdout of the parent.
+ * Otherwise the child will inherit the stderr from the parent. */
 static int log_child(apr_pool_t *p, const char *progname,
-                     apr_file_t **fpin)
+                     apr_file_t **fpin, int dummy_stderr)
 {
     /* Child process code for 'ErrorLog "|..."';
      * may want a common framework for this, since I expect it will
      * be common for other foo-loggers to want this sort of thing...
      */
     apr_status_t rc;
     apr_procattr_t *procattr;
     apr_proc_t *procnew;
+    apr_file_t *errfile;
 
     if (((rc = apr_procattr_create(&procattr, p)) == APR_SUCCESS)
         && ((rc = apr_procattr_cmdtype_set(procattr,
                                            APR_SHELLCMD_ENV)) == APR_SUCCESS)
         && ((rc = apr_procattr_io_set(procattr,
                                       APR_FULL_BLOCK,
                                       APR_NO_PIPE,
                                       APR_NO_PIPE)) == APR_SUCCESS)
         && ((rc = apr_procattr_error_check_set(procattr, 1)) == APR_SUCCESS)
-        && ((rc = apr_procattr_child_errfn_set(procattr, log_child_errfn)) == APR_SUCCESS)) {
+        && ((rc = apr_procattr_child_errfn_set(procattr, log_child_errfn)) == APR_SUCCESS)
+        && (!dummy_stderr 
+            || ((rc = apr_file_open_stdout(&errfile, p)) == APR_SUCCESS
+                && (rc = apr_procattr_child_err_set(procattr, 
+                                                    errfile, 
+                                                    errfile)) == APR_SUCCESS))) {
         char **args;
         const char *pname;
 
         apr_tokenize_to_argv(progname, &args, p);
         pname = apr_pstrdup(p, args[0]);
         procnew = (apr_proc_t *)apr_pcalloc(p, sizeof(*procnew));
