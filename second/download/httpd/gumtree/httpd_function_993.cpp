static void start_connect(struct connection * c)
{
    apr_status_t rv;

#ifdef USE_SSL
    if (ssl == 1) {
        ssl_start_connect(c);
        return;
    }
#endif
    
    if (!(started < requests))
	return;

    c->read = 0;
    c->bread = 0;
    c->keepalive = 0;
    c->cbx = 0;
    c->gotheader = 0;
    c->rwrite = 0;
    if (c->ctx)
        apr_pool_destroy(c->ctx);
    apr_pool_create(&c->ctx, cntxt);

    if ((rv = apr_socket_create(&c->aprsock, destsa->family,
				SOCK_STREAM, c->ctx)) != APR_SUCCESS) {
	apr_err("socket", rv);
    }
    if ((rv = apr_socket_opt_set(c->aprsock, APR_SO_NONBLOCK, 1))
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
            new_pollfd.reqevents = APR_POLLOUT;
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
	    }
	    c->state = STATE_UNCONNECTED;
	    start_connect(c);
	    return;
	}
    }

    /* connected first time */
    c->state = STATE_CONNECTED;
    started++;
    write_request(c);
}