ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "printenv directive does not take tags in %s",
		    r->filename);