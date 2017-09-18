	n = concurrency;
#ifdef USE_SSL
        if (ssl == 1)
            status = APR_SUCCESS;
        else
#endif
	status = apr_poll(readbits, concurrency, &n, aprtimeout);
	if (status != APR_SUCCESS)
	    apr_err("apr_poll", status);

	if (!n) {
	    err("\nServer timed out\n\n");
	}

	for (i = 0; i < concurrency; i++) {
	    /*
	     * If the connection isn't connected how can we check it?
	     */
	    if (con[i].state == STATE_UNCONNECTED)
		continue;

#ifdef USE_SSL
            if (ssl == 1)
                rv = APR_POLLIN;
            else
#endif
	    apr_poll_revents_get(&rv, con[i].aprsock, readbits);
	    /*
	     * Notes: APR_POLLHUP is set after FIN is received on some
	     * systems, so treat that like APR_POLLIN so that we try to read
	     * again.
	     *
	     * Some systems return APR_POLLERR with APR_POLLHUP.  We need to
