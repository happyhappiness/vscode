ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
	    MODNAME ": read failed %s", r->filename);