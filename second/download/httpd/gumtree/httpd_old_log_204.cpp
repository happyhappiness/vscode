ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"Anonymous: Authoritative, Passwd <%s> not accepted",
			sent_pw ? sent_pw : "\'none\'");