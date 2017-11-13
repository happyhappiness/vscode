ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE4, 0, r,
                              "Headers from script '%s':",
                              apr_filepath_name_get(r->filename));