ap_log_error(APLOG_MARK, APLOG_CRIT, 0, main_server,
                         "CGI request received from wrong server instance; "
                         "see ScriptSock directive");