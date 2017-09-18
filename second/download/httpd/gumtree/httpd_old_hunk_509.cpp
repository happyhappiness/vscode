    if (err != NULL) {
        return err;
    }

    ap_daemons_limit = atoi(arg);
    if (ap_daemons_limit > server_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients of %d exceeds ServerLimit value "
                    "of %d servers,", ap_daemons_limit, server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " lowering MaxClients to %d.  To increase, please "
                    "see the ServerLimit", server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                    " directive.");
       ap_daemons_limit = server_limit;
    } 
    else if (ap_daemons_limit < 1) {
	ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: Require MaxClients > 0, setting to 1");
	ap_daemons_limit = 1;
    }
    return NULL;
}

