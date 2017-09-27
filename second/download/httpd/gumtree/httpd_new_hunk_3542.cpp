
    /*
     * XXX: a way to calculate the stats without requiring O(requests) memory
     * XXX: would be nice.
     */
    stats = calloc(requests, sizeof(struct data));
    if (stats == NULL || con == NULL) {
    	err("Cannot allocate memory for result statistics");
    }

    if ((status = apr_pollset_create(&readbits, concurrency, cntxt,
                                     APR_POLLSET_NOCOPY)) != APR_SUCCESS) {
        apr_err("apr_pollset_create failed", status);
