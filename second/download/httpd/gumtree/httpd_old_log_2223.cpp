ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " lowering MaxClients to %d.  To increase, please "
                    "see the ServerLimit", server_limit);