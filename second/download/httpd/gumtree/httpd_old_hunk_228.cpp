
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
