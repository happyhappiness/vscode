ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, r,
		    MODNAME ": subrequest %s got %s",
		    sub_filename, r->content_type);