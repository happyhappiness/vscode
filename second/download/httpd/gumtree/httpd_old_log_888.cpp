ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients of %d exceeds ServerLimit value "
                    "of %d servers,", ap_daemons_limit, server_limit);