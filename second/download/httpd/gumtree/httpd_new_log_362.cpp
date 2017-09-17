ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, NULL,
                 "dyld errors during link edit for file %s\n%s\n",
                 fileName, errorString);