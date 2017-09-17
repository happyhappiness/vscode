ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, r->server,
			"Anonymous: Passwd <%s> Accepted",
			sent_pw ? sent_pw : "\'none\'");