ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,
		     "Unable ro read BS2000 auth file %s",
		     bs2000_authfile);