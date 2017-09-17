ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, r->server,
		     (direct_connect) ? "NoProxy for %s" : "UseProxy for %s",
		     r->uri);