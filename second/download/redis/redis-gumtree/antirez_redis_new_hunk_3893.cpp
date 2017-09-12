    outputlen = getop ? getop*(end-start+1) : end-start+1;
    if (storekey == NULL) {
        /* STORE option not specified, sent the sorting result to client */
        addReplyMultiBulkLen(c,outputlen);
        for (j = start; j <= end; j++) {
            listNode *ln;
            listIter li;
