ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                             "%s: %s%s%s%s", SSL_LIBRARY_NAME, cpE,
                             cpA != NULL ? " [Hint: " : "",
                             cpA != NULL ? cpA : "", cpA != NULL ? "]" : "");