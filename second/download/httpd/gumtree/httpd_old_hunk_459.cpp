    if (err != NULL) {
        return err;
    }

    threads_to_start = atoi(arg);
    if (threads_to_start > thread_limit) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: StartThreads of %d exceeds ThreadLimit value"
                     " of %d threads,", threads_to_start,
                     thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     " lowering StartThreads to %d. To increase, please"
                     " see the", thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     " ThreadLimit directive.");
    }
    else if (threads_to_start < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: Require StartThreads > 0, setting to 1");
        threads_to_start = 1;
    }
    return NULL;
}

