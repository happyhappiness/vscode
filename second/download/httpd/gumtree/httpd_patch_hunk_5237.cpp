                        option));
 }
 
 static void log_pid(apr_pool_t *pool, const char *pidfilename, apr_file_t **pidfile)
 {
     apr_status_t status;
-    char errmsg[120];
     pid_t mypid = getpid();
 
     if (APR_SUCCESS == (status = apr_file_open(pidfile, pidfilename,
                 APR_FOPEN_WRITE | APR_FOPEN_CREATE | APR_FOPEN_TRUNCATE |
                 APR_FOPEN_DELONCLOSE, APR_FPROT_UREAD | APR_FPROT_UWRITE |
                 APR_FPROT_GREAD | APR_FPROT_WREAD, pool))) {
         apr_file_printf(*pidfile, "%" APR_PID_T_FMT APR_EOL_STR, mypid);
     }
     else {
         if (errfile) {
             apr_file_printf(errfile,
-                            "Could not write the pid file '%s': %s" APR_EOL_STR,
-                            pidfilename,
-                            apr_strerror(status, errmsg, sizeof errmsg));
+                            "Could not write the pid file '%s': %pm" APR_EOL_STR,
+                            pidfilename, &status);
         }
         exit(1);
     }
 }
 
 /*
