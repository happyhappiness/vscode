         != APR_SUCCESS) {
        apr_err("socket nonblock", rv);
    }
    c->start = apr_time_now();
    if ((rv = apr_connect(c->aprsock, destsa)) != APR_SUCCESS) {
	if (APR_STATUS_IS_EINPROGRESS(rv)) {
            apr_pollfd_t new_pollfd;
	    c->state = STATE_CONNECTING;
	    c->rwrite = 0;
            new_pollfd.desc_type = APR_POLL_SOCKET;
            new_pollfd.reqevents = APR_POLLIN;
            new_pollfd.desc.s = c->aprsock;
            new_pollfd.client_data = c;
	    apr_pollset_add(readbits, &new_pollfd);
	    return;
	}
	else {
            apr_pollfd_t remove_pollfd;
            remove_pollfd.desc_type = APR_POLL_SOCKET;
            remove_pollfd.desc.s = c->aprsock;
	    apr_pollset_remove(readbits, &remove_pollfd);
	    apr_socket_close(c->aprsock);
	    err_conn++;
	    if (bad++ > 10) {
		fprintf(stderr,
			"\nTest aborted after 10 failures\n\n");
		apr_err("apr_connect()", rv);
