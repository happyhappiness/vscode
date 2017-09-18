	    int cond_status = OK;

	    ap_kill_timeout(r);
	    if ((cgi_status == HTTP_OK) && (r->method_number == M_GET)) {
		cond_status = ap_meets_conditions(r);
	    }
	    ap_overlap_tables(r->err_headers_out, merge,
		AP_OVERLAP_TABLES_MERGE);
	    if (!ap_is_empty_table(cookie_table)) {
		r->err_headers_out = ap_overlay_tables(r->pool,
		    r->err_headers_out, cookie_table);
	    }
	    return cond_status;
	}

	/* if we see a bogus header don't ignore it. Shout and scream */

#ifdef CHARSET_EBCDIC
	    /* Chances are that we received an ASCII header text instead of
	     * the expected EBCDIC header lines. Try to auto-detect:
	     */
	if (!(l = strchr(w, ':'))) {
	    int maybeASCII = 0, maybeEBCDIC = 0;
	    char *cp;

	    for (cp = w; *cp != '\0'; ++cp) {
		if (isprint(*cp) && !isprint(os_toebcdic[*cp]))
		    ++maybeEBCDIC;
		if (!isprint(*cp) && isprint(os_toebcdic[*cp]))
		    ++maybeASCII;
		}
	    if (maybeASCII > maybeEBCDIC) {
		ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			 "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)", r->filename);
		ascii2ebcdic(w, w, cp - w);
	    }
	}
#endif
	if (!(l = strchr(w, ':'))) {
	    char malformed[(sizeof MALFORMED_MESSAGE) + 1
			   + MALFORMED_HEADER_LENGTH_TO_SHOW];

	    strcpy(malformed, MALFORMED_MESSAGE);
	    strncat(malformed, w, MALFORMED_HEADER_LENGTH_TO_SHOW);
