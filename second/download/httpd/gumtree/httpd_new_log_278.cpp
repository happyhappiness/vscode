ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "endif directive does not take tags in %s",
		    r->filename);