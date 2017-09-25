ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: creation of temporary file in directory %s failed",
                                 temp_dir);