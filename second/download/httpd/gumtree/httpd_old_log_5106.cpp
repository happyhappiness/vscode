ap_log_error(APLOG_MARK, APLOG_ALERT, APR_FROM_OS_ERROR(rc), s,
                     "failure allocating shared memory, shutting down");