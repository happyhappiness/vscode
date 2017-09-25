         != APR_SUCCESS) {
        apr_err("socket nonblock", rv);
    }
    c->start = apr_time_now();
    if ((rv = apr_connect(c->aprsock, destsa)) != APR_SUCCESS) {
	if (APR_STATUS_IS_EINPROGRESS(rv)) {
	    c->state = STATE_CONNECTING;
	    c->rwrite = 0;
	    apr_poll_socket_add(readbits, c->aprsock, APR_POLLOUT);
	    return;
	}
	else {
	    apr_poll_socket_remove(readbits, c->aprsock);
	    apr_socket_close(c->aprsock);
	    err_conn++;
	    if (bad++ > 10) {
		fprintf(stderr,
			"\nTest aborted after 10 failures\n\n");
		apr_err("apr_connect()", rv);
