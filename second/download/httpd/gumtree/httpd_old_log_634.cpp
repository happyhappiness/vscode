ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0, server,
		     "No BS2000Account configured - cannot switch to User %s",
		     user_name);