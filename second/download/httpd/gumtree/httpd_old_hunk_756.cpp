    while (done < requests) {
	apr_int32_t n;
	apr_int32_t timed;

	/* check for time limit expiry */
	now = apr_time_now();
	timed = (apr_int32_t)((now - start) / APR_USEC_PER_SEC);
	if (tlimit && timed > (tlimit * 1000)) {
	    requests = done;	/* so stats are correct */
	}

	n = concurrency;
#ifdef USE_SSL
        if (ssl == 1)
            status = APR_SUCCESS;
        else
#endif
	status = apr_poll(readbits, &n, aprtimeout);
	if (status != APR_SUCCESS)
	    apr_err("apr_poll", status);

	if (!n) {
	    err("\nServer timed out\n\n");
	}
