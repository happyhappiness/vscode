ap_log_error(APLOG_MARK, APLOG_ERR, parm->r->server,
		MODNAME ": could not execute `%s'.",
		compr[parm->method].argv[0]);