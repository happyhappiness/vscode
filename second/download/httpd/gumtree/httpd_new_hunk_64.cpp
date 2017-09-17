	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"malformed header in meta file: %s", r->filename);
	    return SERVER_ERROR;
	}

	*l++ = '\0';
	while (*l && ap_isspace(*l))
	    ++l;

	if (!strcasecmp(w, "Content-type")) {
	    char *tmp;
	    /* Nuke trailing whitespace */

	    char *endp = l + strlen(l) - 1;
	    while (endp > l && ap_isspace(*endp))
		*endp-- = '\0';

	    tmp = ap_pstrdup(r->pool, l);
	    ap_content_type_tolower(tmp);
	    r->content_type = tmp;
	}
	else if (!strcasecmp(w, "Status")) {
	    sscanf(l, "%d", &r->status);
	    r->status_line = ap_pstrdup(r->pool, l);
	}
	else {
