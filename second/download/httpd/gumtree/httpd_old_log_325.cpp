ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
		    MODNAME ": subrequest %s got %s",
		    sub_filename, r->content_type);