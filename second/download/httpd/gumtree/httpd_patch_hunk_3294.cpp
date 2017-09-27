          * Only warn on first time through for this pid.
          *
          * XXX: Could just write first time through too, although
          *      that may screw up scripts written to do something
          *      based on the last modification time of the pid file.
          */
-        ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, p,
+        ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, p, APLOGNO(00098)
                       "pid file %s overwritten -- Unclean "
                       "shutdown of previous Apache run?",
                       fname);
     }
 
     if ((rv = apr_file_open(&pid_file, fname,
                             APR_WRITE | APR_CREATE | APR_TRUNCATE,
                             APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD, p))
         != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00099)
                      "could not create %s", fname);
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(00100)
                      "%s: could not log pid to file %s",
                      ap_server_argv0, fname);
         exit(1);
     }
     apr_file_printf(pid_file, "%" APR_PID_T_FMT APR_EOL_STR, mypid);
     apr_file_close(pid_file);
