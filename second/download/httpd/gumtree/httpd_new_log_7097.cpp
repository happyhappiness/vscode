ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE1, 0, r,
                              "Status line from script '%s': %s",
                              apr_filepath_name_get(r->filename), l);