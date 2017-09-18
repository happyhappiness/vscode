    if (err != NULL) {
        return err;
    }

    max_spare_threads = atoi(arg);
    if (max_spare_threads >= thread_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: detected MinSpareThreads set higher than");
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "ThreadLimit. Resetting to %d", thread_limit);
       max_spare_threads = thread_limit;
    }
    return NULL;
}

