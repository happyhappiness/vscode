	    /* read rest next time */
	    if (space) {
		return;
	    }
	    else {
		/* header is in invalid or too big - close connection */
		apr_poll_socket_remove(readbits, c->aprsock);
		apr_socket_close(c->aprsock);
		err_response++;
		if (bad++ > 10) {
		    err("\nTest aborted after 10 failures\n\n");
		}
		start_connect(c);
