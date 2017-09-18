ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                         "System: %s (errno: %d)",
                         strerror(safe_errno), safe_errno);