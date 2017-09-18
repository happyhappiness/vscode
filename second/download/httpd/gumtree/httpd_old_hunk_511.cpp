    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    if (ap_threads_per_child > HARD_THREAD_LIMIT) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: ThreadsPerChild of %d exceeds compile time"
                     " limit of %d threads,", ap_threads_per_child, 
                     HARD_THREAD_LIMIT);
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     " lowering ThreadsPerChild to %d. To increase, please"
                     " see the  HARD_THREAD_LIMIT define in %s.", 
                     HARD_THREAD_LIMIT, AP_MPM_HARD_LIMITS_FILE);
        ap_threads_per_child = HARD_THREAD_LIMIT;
    }
    else if (ap_threads_per_child < 1) {
	ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: Require ThreadsPerChild > 0, setting to 1");
	ap_threads_per_child = 1;
    }
    return NULL;
}

