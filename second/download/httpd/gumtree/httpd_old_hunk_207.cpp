	    if (*s == '-')
		m->in.offset = -m->in.offset;
	}
	else
	    t = l;
	if (*t++ != ')') {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, serv,
			MODNAME ": missing ')' in indirect offset");
	}
	l = t;
    }


