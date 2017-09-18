ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients (%d) is not an integer multiple",
                    max_clients);