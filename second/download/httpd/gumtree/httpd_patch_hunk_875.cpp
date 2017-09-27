     if (!filename) {
         return APR_EGENERAL;
     }
 
     fname = ap_server_root_relative(p, filename);
     if (!fname) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH, 
+        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH,
                      NULL, "Invalid PID file path %s, ignoring.", filename);
         return APR_EGENERAL;
     }
 
     rv = apr_file_open(&pid_file, fname, APR_READ, APR_OS_DEFAULT, p);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
-    /* Ensure null-termination, so that strtol doesn't go crazy. */
     buf = apr_palloc(p, BUFFER_SIZE);
-    buf[BUFFER_SIZE - 1] = '\0';
 
     rv = apr_file_read_full(pid_file, buf, BUFFER_SIZE - 1, &bytes_read);
     if (rv != APR_SUCCESS && rv != APR_EOF) {
         return rv;
     }
 
     /* If we fill the buffer, we're probably reading a corrupt pid file.
      * To be nice, let's also ensure the first char is a digit. */
-    if (bytes_read == BUFFER_SIZE - 1 || !apr_isdigit(*buf)) {
+    if (bytes_read == 0 || bytes_read == BUFFER_SIZE - 1 || !apr_isdigit(*buf)) {
         return APR_EGENERAL;
     }
 
+    buf[bytes_read] = '\0';
     *mypid = strtol(buf, &endptr, 10);
 
     apr_file_close(pid_file);
     return APR_SUCCESS;
 }
 
