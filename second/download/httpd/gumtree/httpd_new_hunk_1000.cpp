        int failed = 1;
        while (connect_addr) {

	    if ((rv = apr_socket_create(&sock, connect_addr->family, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "proxy: FTP: error creating socket");
                connect_addr = connect_addr->next;
		continue;
	    }

#if !defined(TPF) && !defined(BEOS)
	    if (conf->recv_buffer_size > 0
		&& (rv = apr_socket_opt_set(sock, APR_SO_RCVBUF,
