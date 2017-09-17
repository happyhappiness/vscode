	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"malformed header in meta file: %s", r->filename);
	    return SERVER_ERROR;
	}

	*l++ = '\0';
	while (*l && isspace(*l))
	    ++l;

	if (!strcasecmp(w, "Content-type")) {

	    /* Nuke trailing whitespace */

	    char *endp = l + strlen(l) - 1;
	    while (endp > l && isspace(*endp))
		*endp-- = '\0';

	    r->content_type = ap_pstrdup(r->pool, l);
	    ap_str_tolower(r->content_type);
	}
	else if (!strcasecmp(w, "Status")) {
	    sscanf(l, "%d", &r->status);
	    r->status_line = ap_pstrdup(r->pool, l);
	}
	else {
-- apache_1.3.0/src/modules/standard/mod_cgi.c	1998-05-29 06:09:56.000000000 +0800
