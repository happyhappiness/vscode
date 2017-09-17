ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
			    r, error_fmt, tag_val, r->filename);