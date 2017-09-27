                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                          "%s: could not open error log file %s.",
                          ap_server_argv0, fname);
             return DONE;
         }
-
-        apr_file_inherit_set(s->error_log);
     }
 
     return OK;
 }
 
 int ap_open_logs(apr_pool_t *pconf, apr_pool_t *p /* plog */, 
