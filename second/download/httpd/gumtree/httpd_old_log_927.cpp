ap_log_error(APLOG_MARK,APLOG_INFO|APLOG_NOERRNO,rv,NULL,
	    "Registry stored HKLM\\" REGKEY "\\%s value %s", key, value);