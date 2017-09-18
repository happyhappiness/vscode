ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
	             "ISAPI: Invalid module path %s, skipping", filename);