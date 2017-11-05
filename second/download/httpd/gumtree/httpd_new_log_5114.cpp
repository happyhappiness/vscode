ap_log_error(SCRIPT_LOG_MARK, APLOG_ERR, 0, r->server,
                             APLOGNO(02660) "CGI Interface Error: "
                             "Script headers apparently ASCII: (CGI = %s)",
                             r->filename);