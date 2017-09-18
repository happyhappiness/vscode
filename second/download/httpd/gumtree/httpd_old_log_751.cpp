ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " Automatically lowering MaxClients to %d.  To increase,",
                    server_limit);