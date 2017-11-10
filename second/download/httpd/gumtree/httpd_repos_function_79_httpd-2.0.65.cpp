static void test(void)
{
    apr_time_t now;
    apr_int16_t rv;
    long i;
    apr_status_t status;
#ifdef NOT_ASCII
    apr_size_t inbytes_left, outbytes_left;
#endif

    if (isproxy) {
	connecthost = apr_pstrdup(cntxt, proxyhost);
	connectport = proxyport;
    }
    else {
	connecthost = apr_pstrdup(cntxt, hostname);
	connectport = port;
    }

    if (!use_html) {
	printf("Benchmarking %s ", hostname);
	if (isproxy)
	    printf("[through %s:%d] ", proxyhost, proxyport);
	printf("(be patient)%s",
	       (heartbeatres ? "\n" : "..."));
	fflush(stdout);
    }

    now = apr_time_now();

    con = calloc(concurrency * sizeof(struct connection), 1);
    
    stats = calloc(requests * sizeof(struct data), 1);

    if ((status = apr_pollset_create(&readbits, concurrency, cntxt, 0)) != APR_SUCCESS) {
        apr_err("apr_pollset_create failed", status);
    }

    /* setup request */
    if (posting <= 0) {
	sprintf(request, "%s %s HTTP/1.0\r\n"
		"User-Agent: ApacheBench/%s\r\n"
		"%s" "%s" "%s"
		"Host: %s%s\r\n"
		"Accept: */*\r\n"
		"%s" "\r\n",
		(posting == 0) ? "GET" : "HEAD",
		(isproxy) ? fullurl : path,
		AP_AB_BASEREVISION,
		keepalive ? "Connection: Keep-Alive\r\n" : "",
		cookie, auth, host_field, colonhost, hdrs);
    }
    else {
	sprintf(request, "POST %s HTTP/1.0\r\n"
		"User-Agent: ApacheBench/%s\r\n"
		"%s" "%s" "%s"
		"Host: %s%s\r\n"
		"Accept: */*\r\n"
		"Content-length: %" APR_SIZE_T_FMT "\r\n"
		"Content-type: %s\r\n"
		"%s"
		"\r\n",
		(isproxy) ? fullurl : path,
		AP_AB_BASEREVISION,
		keepalive ? "Connection: Keep-Alive\r\n" : "",
		cookie, auth,
		host_field, colonhost, postlen,
		(content_type[0]) ? content_type : "text/plain", hdrs);
    }

    if (verbosity >= 2)
	printf("INFO: POST header == \n---\n%s\n---\n", request);

    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one contineous buffer
     */
    if (posting == 1) {
	char *buff = malloc(postlen + reqlen + 1);
        if (!buff) {
            fprintf(stderr, "error creating request buffer: out of memory\n");
            return;
        }
	strcpy(buff, request);
	strcpy(buff + reqlen, postdata);
	request = buff;
    }

#ifdef NOT_ASCII
    inbytes_left = outbytes_left = reqlen;
    status = apr_xlate_conv_buffer(to_ascii, request, &inbytes_left,
				   request, &outbytes_left);
    if (status || inbytes_left || outbytes_left) {
	fprintf(stderr, "only simple translation is supported (%d/%u/%u)\n",
		status, inbytes_left, outbytes_left);
	exit(1);
    }
#endif				/* NOT_ASCII */

    /* This only needs to be done once */
#ifdef USE_SSL
    if (ssl != 1)
#endif
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
	!= APR_SUCCESS) {
	char buf[120];
	apr_snprintf(buf, sizeof(buf),
		     "apr_sockaddr_info_get() for %s", connecthost);
	apr_err(buf, rv);
    }

    /* ok - lets start */
    start = apr_time_now();

    /* initialise lots of requests */
    for (i = 0; i < concurrency; i++) {
	con[i].socknum = i;
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
	    break;		/* no need to do another round */
	}

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
            rv = nex