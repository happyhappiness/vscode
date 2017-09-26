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
            requests = done;    /* so stats are correct */
            break;      /* no need to do another round */
        }

        n = concurrency;
        status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
        if (status != APR_SUCCESS)
            apr_err("apr_poll", status);

