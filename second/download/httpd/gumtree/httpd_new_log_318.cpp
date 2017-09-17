ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,
		    MODNAME ": mcheck: can't happen: invalid relation %d.",
		    m->reln);