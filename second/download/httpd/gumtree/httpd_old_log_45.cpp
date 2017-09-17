ap_log_error(APLOG_MARK, APLOG_CRIT, r->server,
			"%s pcfg_openfile: unable to check htaccess file, ensure it is readable",
			filename);