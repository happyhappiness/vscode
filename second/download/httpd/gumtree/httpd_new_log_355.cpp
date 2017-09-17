ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,
		     "No BS2000Account configured - cannot switch to User %S",
		     user_name);