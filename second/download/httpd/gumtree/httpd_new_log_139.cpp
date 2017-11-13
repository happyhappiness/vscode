ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "Server configured for an accept lock mechanism that "
                     "cannot be used with perchild.  Falling back to FCNTL.");