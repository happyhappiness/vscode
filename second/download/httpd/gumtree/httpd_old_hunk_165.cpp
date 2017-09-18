    action = r->handler ? r->handler :
	ap_field_noparam(r->pool, r->content_type);
    if ((t = apr_table_get(conf->action_types,
		       action ? action : ap_default_type(r)))) {
	script = t;
	if (r->finfo.filetype == 0) {
	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
			"File does not exist: %s", r->filename);
	    return HTTP_NOT_FOUND;
	}
    }

    if (script == NULL)
