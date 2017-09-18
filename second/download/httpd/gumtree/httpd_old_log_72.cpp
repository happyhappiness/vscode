ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, cmd->server,
	    "ISAPI: %s isn't a regular file, skipping", fspec);