
    do {
        apr_int32_t n;
        const apr_pollfd_t *pollresults;

        n = concurrency;
        status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
        if (status != APR_SUCCESS)
            apr_err("apr_poll", status);

        if (!n) {
            err("\nServer timed out\n\n");
        }
