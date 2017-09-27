         return APR_EGENERAL;
     }
 
     fname = ap_server_root_relative(p, filename);
     if (!fname) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH,
-                     NULL, "Invalid PID file path %s, ignoring.", filename);
+                     NULL, APLOGNO(00101) "Invalid PID file path %s, ignoring.", filename);
         return APR_EGENERAL;
     }
 
     rv = apr_file_open(&pid_file, fname, APR_READ, APR_OS_DEFAULT, p);
     if (rv != APR_SUCCESS) {
         return rv;
