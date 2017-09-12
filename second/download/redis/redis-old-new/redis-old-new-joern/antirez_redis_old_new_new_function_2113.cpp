void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[4096];
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
        redisLog(REDIS_NOTICE,"I/O error reading from node link: %s",
            (nread == 0) ? "connection closed" : strerror(errno));
        handleLinkIOError(link);
        return;
    } else {
        /* Read data and recast the pointer to the new buffer. */
        link->rcvbuf = sdscatlen(link->rcvbuf,buf,nread);
        hdr = (clusterMsg*) link->rcvbuf;
        rcvbuflen += nread;
    }

    /* Total length obtained? read the payload now instead of burning
     * cycles waiting for a new event to fire. */
    if (rcvbuflen == 4) goto again;

    /* Whole packet in memory? We can process it. */
    if (rcvbuflen == ntohl(hdr->totlen)) {
        if (clusterProcessPacket(link)) {
            sdsfree(link->rcvbuf);
            link->rcvbuf = sdsempty();
            rcvbuflen = 0; /* Useless line of code currently... defensive. */
        }
    }
}