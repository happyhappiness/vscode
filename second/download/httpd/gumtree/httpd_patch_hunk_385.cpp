             ap_log_error(APLOG_MARK, APLOG_STARTUP, APR_EBADPATH, NULL,
                          "%s: Invalid error log path %s.",
                          ap_server_argv0, s->error_fname);
             return DONE;
         }
         if ((rc = apr_file_open(&s->error_log, fname,
-                               APR_APPEND | APR_READ | APR_WRITE | APR_CREATE,
+                               APR_APPEND | APR_WRITE | APR_CREATE | APR_LARGEFILE,
                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                          "%s: could not open error log file %s.",
                          ap_server_argv0, fname);
             return DONE;
         }
