ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
	    "ISAPI: unable to stat(%s), skipping", fspec);