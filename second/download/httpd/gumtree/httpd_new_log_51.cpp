ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		     "Invalid URI in request %s", r->the_request);