	if (r->filename[strlen(r->filename) - 1] != '/') {
	    r->filename = ap_pstrcat(r->pool, r->filename, "/", NULL);
	}
	return index_directory(r, d);
    }
    else {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		     "Directory index forbidden by rule: %s", r->filename);
	return HTTP_FORBIDDEN;
    }
}


