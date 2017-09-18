    r->read_length     = 0;
    r->read_body       = REQUEST_NO_BODY;

    r->status          = HTTP_REQUEST_TIME_OUT;  /* Until we get a request */
    r->the_request     = NULL;

#ifdef CHARSET_EBCDIC
    ap_bsetflag(r->connection->client, B_ASCII2EBCDIC|B_EBCDIC2ASCII, 1);
#endif

    /* Get the request... */

    ap_keepalive_timeout("read request line", r);
    if (!read_request_line(r)) {
        ap_kill_timeout(r);
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                         "request failed: URI too long");
            ap_send_error_response(r, 0);
            ap_bflush(r->connection->client);
	    ap_log_transaction(r);
            return r;
	}
        return NULL;
    }
    if (!r->assbackwards) {
        ap_hard_timeout("read request headers", r);
        get_mime_headers(r);
        ap_kill_timeout(r);
        if (r->status != HTTP_REQUEST_TIME_OUT) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                         "request failed: error reading the headers");
            ap_send_error_response(r, 0);
            ap_bflush(r->connection->client);
	    ap_log_transaction(r);
            return r;
	}
    }
    else {
        ap_kill_timeout(r);
    }

    r->status = HTTP_OK;                         /* Until further notice. */

    /* update what we think the virtual host is based on the headers we've
     * now read
     */
