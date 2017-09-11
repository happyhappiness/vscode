    ssize_t nread;
    clusterMsg *hdr;
    clusterLink *link = (clusterLink*) privdata;
    int readlen, rcvbuflen;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);

again:
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
        }
        readlen = ntohl(hdr->totlen) - rcvbuflen;
    }

    nread = read(fd,buf,readlen);
    if (nread == -1 && errno == EAGAIN) return; /* No more data ready. */

    if (nread <= 0) {
        /* I/O error... */
