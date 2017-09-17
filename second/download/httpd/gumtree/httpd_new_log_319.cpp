ap_log_rerror(APLOG_MARK, APLOG_ERR, parm->r,
		MODNAME ": could not execute `%s'.",
		compr[parm->method].argv[0]);