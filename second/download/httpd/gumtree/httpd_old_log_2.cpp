ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, APR_SUCCESS, r,
			"Anonymous: Authoritative, Passwd <%s> not accepted",
			sent_pw ? sent_pw : "\'none\'");