ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot reinit SSLMutex with file `%s'",
                         mc->szMutexFile);