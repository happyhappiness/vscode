ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    MODNAME ": couldn't spawn uncompress process: %s", r->uri);