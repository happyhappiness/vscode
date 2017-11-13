ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "set dumpable failed - this child will not coredump"
                         " after software errors");