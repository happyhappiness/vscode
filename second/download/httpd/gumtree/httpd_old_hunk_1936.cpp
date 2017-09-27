           (heartbeatres ? "\n" : "..."));
    fflush(stdout);
    }

    con = calloc(concurrency, sizeof(struct connection));

    stats = calloc(requests, sizeof(struct data));

    if ((status = apr_pollset_create(&readbits, concurrency, cntxt, 0)) != APR_SUCCESS) {
        apr_err("apr_pollset_create failed", status);
    }

    /* add default headers if necessary */
    if (!opt_host) {
        /* Host: header not overridden, add default value to hdrs */
