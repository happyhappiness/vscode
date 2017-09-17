    r->read_length     = 0;
    r->read_body       = REQUEST_NO_BODY;

    r->status          = HTTP_REQUEST_TIME_OUT;  /* Until we get a request */
    r->the_request     = NULL;

    /* Get the request... */

#ifdef CHARSET_EBCDIC
    ap_bsetflag(r->connection->client, B_ASCII2EBCDIC|B_EBCDIC2ASCII, 1);
#endif /* CHARSET_EBCDIC */
    ap_keepalive_timeout("read request line", r);
    if (!read_request_line(r)) {
        ap_kill_timeout(r);
	if (r->status != HTTP_REQUEST_TIME_OUT) {
	    /* we must have had an error.*/
	    ap_log_transaction(r);
	}
        return NULL;
    }
    if (!r->assbackwards) {
        ap_hard_timeout("read request headers", r);
        get_mime_headers(r);
        if (r->status != HTTP_REQUEST_TIME_OUT) {/* we must have had an error.*/
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		         "request failed for %s: error reading the headers",
		         ap_get_remote_host(r->connection, r->per_dir_config, 
					    REMOTE_NAME));
	    ap_log_transaction(r);
	    return NULL;
	}

    }
    ap_kill_timeout(r);

    r->status = HTTP_OK;                         /* Until further notice. */

    /* update what we think the virtual host is based on the headers we've
     * now read
     */
