ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
		    MODNAME ": mcheck: can't happen: invalid relation %d.",
		    m->reln);