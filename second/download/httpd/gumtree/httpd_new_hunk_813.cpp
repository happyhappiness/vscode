	n = concurrency;
#ifdef USE_SSL
        if (ssl == 1)
            status = APR_SUCCESS;
        else
#endif
	status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
	if (status != APR_SUCCESS)
	    apr_err("apr_poll", status);

	if (!n) {
	    err("\nServer timed out\n\n");
	}

	for (i = 0; i < n; i++) {
            const apr_pollfd_t *next_fd = &(pollresults[i]);
            struct connection *c = next_fd->client_data;

	    /*
	     * If the connection isn't connected how can we check it?
	     */
	    if (c->state == STATE_UNCONNECTED)
		continue;

#ifdef USE_SSL
            if (ssl == 1)
                rv = APR_POLLIN;
            else
#endif
            rv = next_fd->rtnevents;

	    /*
	     * Notes: APR_POLLHUP is set after FIN is received on some
	     * systems, so treat that like APR_POLLIN so that we try to read
	     * again.
	     *
	     * Some systems return APR_POLLERR with APR_POLLHUP.  We need to
