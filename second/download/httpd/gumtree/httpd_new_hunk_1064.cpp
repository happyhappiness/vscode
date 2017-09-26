	start_connect(&con[i]);
    }

    while (done < requests) {
	apr_int32_t n;
	apr_int32_t timed;
            const apr_pollfd_t *pollresults;

	/* check for time limit expiry */
	now = apr_time_now();
	timed = (apr_int32_t)apr_time_sec(now - start);
	if (tlimit && timed >= tlimit) {
	    requests = done;	/* so stats are correct */
            break;      /* no need to do another round */
	}

	n = concurrency;
	status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
	if (status != APR_SUCCESS)
	    apr_err("apr_poll", status);

	if (!n) {
	    err("\nServer timed out\n\n");
	}

	for (i = 0; i < n; i++) {
            const apr_pollfd_t *next_fd = &(pollresults[i]);
            struct connection *c;

                c = next_fd->client_data;

	    /*
	     * If the connection isn't connected how can we check it?
	     */
	    if (c->state == STATE_UNCONNECTED)
		continue;

            rv = next_fd->rtnevents;

#ifdef USE_SSL
            if (c->state == STATE_CONNECTED && c->ssl && SSL_in_init(c->ssl)) {
                ssl_proceed_handshake(c);
                continue;
            }
#endif

	    /*
	     * Notes: APR_POLLHUP is set after FIN is received on some
	     * systems, so treat that like APR_POLLIN so that we try to read
	     * again.
	     *
