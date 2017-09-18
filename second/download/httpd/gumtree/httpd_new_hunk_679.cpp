
    /* try each IP address until we connect successfully */
    {
        int failed = 1;
        while (connect_addr) {

	    if ((rv = apr_socket_create(&sock, connect_addr->family, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "proxy: FTP: error creating socket");
		continue;
	    }

#if !defined(TPF) && !defined(BEOS)
	    if (conf->recv_buffer_size > 0
		&& (rv = apr_socket_opt_set(sock, APR_SO_RCVBUF,
                                            conf->recv_buffer_size))) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "apr_socket_opt_set(APR_SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
	    }
#endif

	    if (APR_SUCCESS != (rv = apr_socket_opt_set(sock, APR_SO_REUSEADDR, one))) {
		apr_socket_close(sock);
#ifndef _OSD_POSIX              /* BS2000 has this option "always on" */
		ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "proxy: FTP: error setting reuseaddr option: apr_socket_opt_set(APR_SO_REUSEADDR)");
		continue;
#endif                          /* _OSD_POSIX */
	    }

	    /* Set a timeout on the socket */
	    if (conf->timeout_set == 1) {
		apr_socket_timeout_set(sock, conf->timeout);
	    }
	    else {
		apr_socket_timeout_set(sock, r->server->timeout);
	    }

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: FTP: fam %d socket created, trying to connect to %pI (%s)...", 
                         connect_addr->family, connect_addr, connectname);

            /* make the connection out of the socket */
            rv = apr_connect(sock, connect_addr);

            /* if an error occurred, loop round and try again */
            if (rv != APR_SUCCESS) {
		apr_socket_close(sock);
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "proxy: FTP: attempt to connect to %pI (%s) failed", connect_addr, connectname);
                connect_addr = connect_addr->next;
                continue;
            }

