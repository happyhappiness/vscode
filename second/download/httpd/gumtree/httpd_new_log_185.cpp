ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, r->server,
		 "proxy: Bad HTTP/%d.%d header returned by %s (%s)",
		 major, minor, r->uri, r->method);