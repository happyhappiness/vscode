     apr_status_t rc;
     char *filename = ap_server_root_relative(p, fname);
     if (!filename) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT,
                      APR_EBADPATH, NULL, "Invalid -E error log file %s",
                      fname);
-        exit(1);
+        return APR_EBADPATH;
     }
     if ((rc = apr_file_open(&stderr_file, filename,
                             APR_APPEND | APR_READ | APR_WRITE | APR_CREATE,
                             APR_OS_DEFAULT, p)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                      "%s: could not open error log file %s.",
