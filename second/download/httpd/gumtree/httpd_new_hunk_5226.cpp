        printf("[through %s:%d] ", proxyhost, proxyport);
    printf("(be patient)%s",
           (heartbeatres ? "\n" : "..."));
    fflush(stdout);
    }

    con = xcalloc(concurrency, sizeof(struct connection));

    /*
     * XXX: a way to calculate the stats without requiring O(requests) memory
     * XXX: would be nice.
     */
    stats = xcalloc(requests, sizeof(struct data));

    if ((status = apr_pollset_create(&readbits, concurrency, cntxt,
                                     APR_POLLSET_NOCOPY)) != APR_SUCCESS) {
        apr_err("apr_pollset_create failed", status);
    }

