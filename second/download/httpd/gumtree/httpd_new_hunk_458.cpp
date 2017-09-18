    if (err != NULL) {
        return err;
    }

    num_daemons = atoi(arg);
    if (num_daemons > server_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: NumServers of %d exceeds ServerLimit value "
                    "of %d servers,", num_daemons, server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " lowering NumServers to %d.  To increase, please "
                    "see the", server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " ServerLimit directive.");
       num_daemons = server_limit;
    } 
    else if (num_daemons < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: Require NumServers > 0, setting to 1");
        num_daemons = 1;
    }
    return NULL;
}

