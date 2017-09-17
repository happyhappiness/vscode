ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "else directive does not take tags in %s",
		    r->filename);