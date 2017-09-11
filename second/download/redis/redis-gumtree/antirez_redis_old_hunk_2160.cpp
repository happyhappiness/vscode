
    while(1) { /* Read as long as there is data to read. */
        rcvbuflen = sdslen(link->rcvbuf);
        if (rcvbuflen < 4) {
            /* First, obtain the first four bytes to get the full message
             * length. */
            readlen = 4 - rcvbuflen;
        } else {
            /* Finally read the full message. */
            hdr = (clusterMsg*) link->rcvbuf;
            if (rcvbuflen == 4) {
                /* Perform some sanity check on the message length. */
                if (ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN) {
                    redisLog(REDIS_WARNING,
                        "Bad message length received from Cluster bus.");
                    handleLinkIOError(link);
                    return;
                }
