ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
			    r->server, error_fmt, tag_val, r->filename);