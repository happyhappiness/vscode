ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "client used wrong authentication scheme: %s for %s", 
		    scheme, r->uri);