    while (done < requests) {
	apr_int32_t n;
	apr_int32_t timed;

	/* check for time limit expiry */
	now = apr_time_now();
	timed = (apr_int32_t)apr_time_sec(now - start);
	if (tlimit && timed >= tlimit) {
	    requests = done;	/* so stats are correct */
	    break;		/* no need to do another round */
	}

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
