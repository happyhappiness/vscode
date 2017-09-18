    /* If we are connecting through a remote proxy, we need to pass
     * the CONNECT request on to it.
     */
    if (proxyport) {
	/* FIXME: Error checking ignored.
	 */
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		     "proxy: CONNECT: sending the CONNECT request to the remote proxy");
        nbytes = apr_snprintf(buffer, sizeof(buffer),
			      "CONNECT %s HTTP/1.0" CRLF, r->uri);
        apr_send(sock, buffer, &nbytes);
        nbytes = apr_snprintf(buffer, sizeof(buffer),
			      "Proxy-agent: %s" CRLF CRLF, ap_get_server_version());
        apr_send(sock, buffer, &nbytes);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		     "proxy: CONNECT: Returning 200 OK Status");
        nbytes = apr_snprintf(buffer, sizeof(buffer),
			      "HTTP/1.0 200 Connection Established" CRLF);
        apr_send(client_socket, buffer, &nbytes);
        nbytes = apr_snprintf(buffer, sizeof(buffer),
			      "Proxy-agent: %s" CRLF CRLF, ap_get_server_version());
#if 0
        /* This is safer code, but it doesn't work yet.  I'm leaving it 
         * here so that I can fix it later.
         */
        apr_send(r->connection->client_socket, buffer, &nbytes);
        r->status = HTTP_OK;
        r->header_only = 1;
        apr_table_set(r->headers_out, "Proxy-agent: %s", ap_get_server_version());
        ap_rflush(r);
#endif
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		 "proxy: CONNECT: setting up poll()");

    /*
     * Step Four: Handle Data Transfer
     *
     * Handle two way transfer of data over the socket (this is a tunnel).
