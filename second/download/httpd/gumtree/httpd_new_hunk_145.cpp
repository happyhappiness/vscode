	struct dirconn_entry *list = (struct dirconn_entry *) conf->dirconn->elts;

	for (direct_connect = ii = 0; ii < conf->dirconn->nelts && !direct_connect; ii++) {
	    direct_connect = list[ii].matcher(&list[ii], r);
	}
#if DEBUGGING
	ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, r,
		     (direct_connect) ? "NoProxy for %s" : "UseProxy for %s",
		     r->uri);
#endif
    }

/* firstly, try a proxy, unless a NoProxy directive is active */
