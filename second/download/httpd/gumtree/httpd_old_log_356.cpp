ap_log_error(APLOG_MARK, APLOG_ALERT, server,
		     "Unable to open bs2000 auth file %s for User %s",
		     bs2000_authfile, user_name);