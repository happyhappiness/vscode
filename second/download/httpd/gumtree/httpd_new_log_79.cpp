ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
	    "mod_file_cache: %s isn't a regular file, skipping", fspec);