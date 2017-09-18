    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    if (ap_threads_per_child > thread_limit) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                     "value of %d", ap_threads_per_child,
                     thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "threads, lowering ThreadsPerChild to %d. To increase, please"
                     " see the", thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     " ThreadLimit directive.");
        ap_threads_per_child = thread_limit;
    }
    else if (ap_threads_per_child < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: Require ThreadsPerChild > 0, setting to 1");
        ap_threads_per_child = 1;
    }
    return NULL;
}

