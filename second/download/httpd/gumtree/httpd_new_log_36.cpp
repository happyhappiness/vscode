ap_log_error(APLOG_MARK, APLOG_ERR, NULL, 
	    "Invalid path in os_stat: \"%s\", should have a drive letter "
	    "or be a UNC path", szPath);