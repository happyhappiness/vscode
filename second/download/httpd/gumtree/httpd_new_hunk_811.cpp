	    /* read rest next time */
	    if (space) {
		return;
	    }
	    else {
		/* header is in invalid or too big - close connection */
                apr_pollfd_t remove_pollfd;
                remove_pollfd.desc_type = APR_POLL_SOCKET;
                remove_pollfd.desc.s = c->aprsock;
                apr_pollset_remove(readbits, &remove_pollfd);
		apr_socket_close(c->aprsock);
		err_response++;
		if (bad++ > 10) {
		    err("\nTest aborted after 10 failures\n\n");
		}
		start_connect(c);
