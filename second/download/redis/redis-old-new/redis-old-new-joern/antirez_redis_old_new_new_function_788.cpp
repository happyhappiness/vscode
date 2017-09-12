void clusterWriteHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    clusterLink *link = (clusterLink*) privdata;
    ssize_t nwritten;
    UNUSED(el);
    UNUSED(mask);

    nwritten = write(fd, link->sndbuf, sdslen(link->sndbuf));
    if (nwritten <= 0) {
        serverLog(LL_DEBUG,"I/O error writing to node link: %s",
            strerror(errno));
        handleLinkIOError(link);
        return;
    }
    sdsrange(link->sndbuf,nwritten,-1);
    if (sdslen(link->sndbuf) == 0)
        aeDeleteFileEvent(server.el, link->fd, AE_WRITABLE);
}