ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
		    MODNAME ": invalid type %d in mcheck().", m->type);