 #ifdef AP_HAVE_RELIABLE_PIPED_LOGS
 /* forward declaration */
 static void piped_log_maintenance(int reason, void *data, apr_wait_t status);
 
 static int piped_log_spawn(piped_log *pl)
 {
-    int rc;
+    int rc = 0;
     apr_procattr_t *procattr;
     apr_proc_t *procnew = NULL;
     apr_status_t status;
 
     if (((status = apr_procattr_create(&procattr, pl->p)) != APR_SUCCESS) ||
         ((status = apr_procattr_child_in_set(procattr,
                                              ap_piped_log_read_fd(pl),
                                              ap_piped_log_write_fd(pl)))
-        != APR_SUCCESS)) {
+        != APR_SUCCESS) ||
+        ((status = apr_procattr_child_errfn_set(procattr, log_child_errfn))
+         != APR_SUCCESS) ||
+        ((status = apr_procattr_error_check_set(procattr, 1)) != APR_SUCCESS)) {
         char buf[120];
         /* Something bad happened, give up and go away. */
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                      "piped_log_spawn: unable to setup child process '%s': %s",
                      pl->program, apr_strerror(status, buf, sizeof(buf)));
         rc = -1;
