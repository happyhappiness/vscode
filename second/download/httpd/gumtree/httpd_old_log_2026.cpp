ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     ap_server_conf,
                                     "server is within MinSpareThreads of MaxClients, consider"
                                     " raising the MaxClients setting");