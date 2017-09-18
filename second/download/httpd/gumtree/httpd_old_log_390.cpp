ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
			     "3)IP-Match: %s[%s] <-> ", host, 
			     inet_ntoa(*ip));