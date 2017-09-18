ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "Parsed mask %s", inet_ntoa(New->mask));