ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,
		     "Use the 'BS2000AuthFile <passwdfile>' directive to specify "
		     "an authorization file for User %s",
		     user_name);