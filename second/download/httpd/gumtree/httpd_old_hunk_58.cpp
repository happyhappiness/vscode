	    return cond_status;

	}



	/* if we see a bogus header don't ignore it. Shout and scream */



	if (!(l = strchr(w, ':'))) {

	    char malformed[(sizeof MALFORMED_MESSAGE) + 1 + MALFORMED_HEADER_LENGTH_TO_SHOW];

	    strcpy(malformed, MALFORMED_MESSAGE);

	    strncat(malformed, w, MALFORMED_HEADER_LENGTH_TO_SHOW);



	    if (!buffer)

		/* Soak up all the script output --- may save an outright kill */

		while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data))

		    continue;



	    ap_kill_timeout(r);

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

			"%s: %s", malformed, r->filename);

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

	/*

	 * If the script returned a specific status, that's what

	 * we'll use - otherwise we assume 200 OK.

	 */

	else if (!strcasecmp(w, "Status")) {

