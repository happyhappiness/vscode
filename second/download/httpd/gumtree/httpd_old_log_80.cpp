ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, cmd->server,
	    "mod_file_cache: %s is too large to cache, skipping", fspec);