ap_log_rerror(APLOG_MARK, APLOG_CRIT, r,
			"%s pcfg_openfile: unable to check htaccess file, ensure it is readable",
			filename);