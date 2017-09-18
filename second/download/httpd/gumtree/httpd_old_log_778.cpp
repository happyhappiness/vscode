ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: NumServers of %d exceeds ServerLimit value "
                    "of %d servers,", num_daemons, server_limit);