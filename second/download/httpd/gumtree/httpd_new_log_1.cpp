ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r,
			"Anonymous: Passwd <%s> Accepted",
			sent_pw ? sent_pw : "\'none\'");