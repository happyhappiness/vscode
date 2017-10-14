ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "Couldn't start piped log process '%s'.",
                     (program == NULL) ? "NULL" : program);