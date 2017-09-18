    if (err != NULL) {
        return err;
    }

    ap_thread_limit = atoi(arg);
    if (ap_thread_limit > HARD_THREAD_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: MaxClients of %d exceeds compile time limit "
                    "of %d servers,", ap_thread_limit, HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " lowering MaxClients to %d.  To increase, please "
                    "see the", HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " HARD_THREAD_LIMIT define in server/mpm/beos/mpm_default.h.");
       ap_thread_limit = HARD_THREAD_LIMIT;
    } 
    else if (ap_thread_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: Require MaxClients > 0, setting to %d", HARD_THREAD_LIMIT);
        ap_thread_limit = HARD_THREAD_LIMIT;
    }
    return NULL;
}

