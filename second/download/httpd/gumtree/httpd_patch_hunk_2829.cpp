     if (*cfg->logname == '|') {
         piped_log *pl;
         const char *pname = ap_server_root_relative(p, cfg->logname + 1);
 
         pl = ap_open_piped_log(p, pname);
         if (pl == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00650)
                          "couldn't spawn forensic log pipe %s", cfg->logname);
             return 0;
         }
         cfg->fd = ap_piped_log_write_fd(pl);
     }
     else {
         const char *fname = ap_server_root_relative(p, cfg->logname);
         apr_status_t rv;
 
         if ((rv = apr_file_open(&cfg->fd, fname,
                                 APR_WRITE | APR_APPEND | APR_CREATE,
                                 APR_OS_DEFAULT, p)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00651)
                          "could not open forensic log file %s.", fname);
             return 0;
         }
     }
 
     return 1;
