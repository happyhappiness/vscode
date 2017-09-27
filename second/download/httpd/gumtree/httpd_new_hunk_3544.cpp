                        status, inbytes_left, outbytes_left);
        exit(1);
    }
#endif              /* NOT_ASCII */

    /* This only needs to be done once */
    if ((rv = apr_sockaddr_info_get(&mysa, myhost, APR_UNSPEC, 0, 0, cntxt)) != APR_SUCCESS) {
        char buf[120];
        apr_snprintf(buf, sizeof(buf),
                 "apr_sockaddr_info_get() for %s", myhost);
        apr_err(buf, rv);
    }

    /* This too */
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
       != APR_SUCCESS) {
        char buf[120];
        apr_snprintf(buf, sizeof(buf),
                 "apr_sockaddr_info_get() for %s", connecthost);
        apr_err(buf, rv);
    }

    /* ok - lets start */
    start = lasttime = apr_time_now();
    stoptime = tlimit ? (start + apr_time_from_sec(tlimit)) : AB_MAX;

#ifdef SIGINT
    /* Output the results if the user terminates the run early. */
    apr_signal(SIGINT, output_results);
#endif

    /* initialise lots of requests */
    for (i = 0; i < concurrency; i++) {
        con[i].socknum = i;
        start_connect(&con[i]);
    }

    do {
        apr_int32_t n;
        const apr_pollfd_t *pollresults, *pollfd;

        n = concurrency;
        do {
            status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
        } while (APR_STATUS_IS_EINTR(status));
        if (status != APR_SUCCESS)
            apr_err("apr_pollset_poll", status);

        for (i = 0, pollfd = pollresults; i < n; i++, pollfd++) {
            struct connection *c;

            c = pollfd->client_data;

            /*
             * If the connection isn't connected how can we check it?
             */
            if (c->state == STATE_UNCONNECTED)
                continue;

            rtnev = pollfd->rtnevents;

#ifdef USE_SSL
            if (c->state == STATE_CONNECTED && c->ssl && SSL_in_init(c->ssl)) {
                ssl_proceed_handshake(c);
                continue;
            }
