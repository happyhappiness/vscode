    if (err != NULL) {
        return err;
    }

    ap_threads_limit = atoi(arg);
    if (ap_threads_limit > HARD_THREAD_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxThreads of %d exceeds compile time limit "
                    "of %d threads,", ap_threads_limit, HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " lowering MaxThreads to %d.  To increase, please "
                    "see the", HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                    " HARD_THREAD_LIMIT define in %s.",
                    AP_MPM_HARD_LIMITS_FILE);
       ap_threads_limit = HARD_THREAD_LIMIT;
    } 
    else if (ap_threads_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
            "WARNING: Require MaxThreads > 0, setting to 1");
        ap_threads_limit = 1;
    }
    return NULL;
}

