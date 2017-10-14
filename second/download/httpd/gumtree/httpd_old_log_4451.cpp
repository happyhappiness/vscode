ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: write to temporary file %s failed",
                                 tmpfile_name);