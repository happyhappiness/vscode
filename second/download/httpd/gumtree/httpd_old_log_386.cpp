ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "1)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(addr));