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
