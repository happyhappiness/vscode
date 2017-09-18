	else if (tnow > c->connect + aprtimeout) {
	    printf("Send request timed out!\n");
	    close_connection(c);
	    return;
	}

	e = apr_send(c->aprsock, request + c->rwrote, &l);

	/*
	 * Bail early on the most common case
	 */
	if (l == c->rwrite)
	    break;

	if (e != APR_SUCCESS) {
	    /*
	     * Let's hope this traps EWOULDBLOCK too !
	     */
	    if (!APR_STATUS_IS_EAGAIN(e)) {
		epipe++;
		printf("Send request failed!\n");
		close_connection(c);
	    }
	    return;
	}
	c->rwrote += l;
	c->rwrite -= l;
    } while (1);

    totalposted += c->rwrite;
    c->state = STATE_READ;
    c->endwrite = apr_time_now();
    apr_poll_socket_add(readbits, c->aprsock, APR_POLLIN);
}

/* --------------------------------------------------------- */

/* calculate and output results */
