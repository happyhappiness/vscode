
/* Asynchronously read the SYNC payload we receive from a master */
void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
    unsigned char buf[4096];
    ssize_t nread, readlen;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
    REDIS_NOTUSED(mask);

    readlen = (server.repl_transfer_left < (signed)sizeof(buf)) ?
        server.repl_transfer_left : (signed)sizeof(buf);
    nread = read(fd,buf,readlen);
