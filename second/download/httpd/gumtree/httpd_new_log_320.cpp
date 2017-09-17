ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    MODNAME ": couldn't spawn uncompress process: %s", r->uri);