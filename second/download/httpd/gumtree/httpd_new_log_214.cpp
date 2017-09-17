ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    "could not open dbm auth file: %s", auth_dbmpwfile);