    if (err != NULL) {
        return err;
    }

    max_threads = atoi(arg);
    if (max_threads > thread_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: detected MaxThreadsPerChild set higher than");
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "ThreadLimit. Resetting to %d", thread_limit);
       max_threads = thread_limit;
    }
    return NULL;
}

