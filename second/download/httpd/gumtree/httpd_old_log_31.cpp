ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, r->server,
			"Anonymous: Passwd <%s> Accepted",
			send_pw ? send_pw : "\'none\'");