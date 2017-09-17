         * Client sent us a HTTP/1.1 or later request without telling us the
         * hostname, either with a full URL or a Host: header. We therefore
         * need to (as per the 1.1 spec) send an error.  As a special case,
	 * HTTP/1.1 mentions twice (S9, S14.23) that a request MUST contain
	 * a Host: header, and the server MUST respond with 400 if it doesn't.
         */
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
               "client sent HTTP/1.1 request without hostname (see RFC2068 section 9, and 14.23): %s", r->uri);
        ap_die(BAD_REQUEST, r);
        return;
    }

    /* Ignore embedded %2F's in path for proxy requests */
