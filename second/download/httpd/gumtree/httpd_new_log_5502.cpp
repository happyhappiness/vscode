ap_log_error(SCRIPT_LOG_MARK, APLOG_ERR, 0, r->server,
                             "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)",
                             r->filename);