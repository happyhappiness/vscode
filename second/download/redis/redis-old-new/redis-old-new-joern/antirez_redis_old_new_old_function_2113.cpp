void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[4096];
    ssize_t nread;
    clusterMsg *hdr;
    clusterLink *link = (clusterLink*) privdata;
    int readlen;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);

again:
    if (sdslen(link->rcvbuf) >= 4) {
        hdr = (clusterMsg*) link->rcvbuf;
        readlen = ntohl(hdr->totlen) - sdslen(link->rcvbuf);
    } else {
        readlen = 4 - sdslen(link->rcvbuf);
    }

    nread = read(fd,buf,readlen);
    if (nread == -1 && errno == EAGAIN) return; /* Just no data */

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
    }

    /* Total length obtained? read the payload now instead of burning
     * cycles waiting for a new event to fire. */
    if (sdslen(link->rcvbuf) == 4) goto again;

    /* Whole packet in memory? We can process it. */
    if (sdslen(link->rcvbuf) == ntohl(hdr->totlen)) {
        if (clusterProcessPacket(link)) {
            sdsfree(link->rcvbuf);
            link->rcvbuf = sdsempty();
        }
    }
}