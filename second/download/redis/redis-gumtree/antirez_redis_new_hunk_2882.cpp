    /* Send command output to the output buffer, performing the specified
     * GET/DEL/INCR/DECR operations if any. */
    outputlen = getop ? getop*(end-start+1) : end-start+1;
    if (int_convertion_error) {
        addReplyError(c,"One or more scores can't be converted into double");
    } else if (storekey == NULL) {
        /* STORE option not specified, sent the sorting result to client */
        addReplyMultiBulkLen(c,outputlen);
        for (j = start; j <= end; j++) {
