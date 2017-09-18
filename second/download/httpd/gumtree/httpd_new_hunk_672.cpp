
    /* Add the server side to the poll */
    apr_poll_socket_add(pollfd, sock, APR_POLLIN);

    while (1) { /* Infinite loop until error (one side closes the connection) */
/*	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "proxy: CONNECT: going to sleep (poll)");*/
        if ((rv = apr_poll(pollfd, 2, &pollcnt, -1)) != APR_SUCCESS)
        {
	    apr_socket_close(sock);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "proxy: CONNECT: error apr_poll()");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
/*	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
