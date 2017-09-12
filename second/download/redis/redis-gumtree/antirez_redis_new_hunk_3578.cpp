
/* Asynchronously read the SYNC payload we receive from a master */
void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[4096];
    ssize_t nread, readlen;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
    REDIS_NOTUSED(mask);

    /* If repl_transfer_left == -1 we still have to read the bulk length
     * from the master reply. */
    if (server.repl_transfer_left == -1) {
        if (syncReadLine(fd,buf,1024,3600) == -1) {
            redisLog(REDIS_WARNING,
                "I/O error reading bulk count from MASTER: %s",
                strerror(errno));
            replicationAbortSyncTransfer();
            return;
        }
        if (buf[0] == '-') {
            redisLog(REDIS_WARNING,
                "MASTER aborted replication with an error: %s",
                buf+1);
            replicationAbortSyncTransfer();
            return;
        } else if (buf[0] != '$') {
            redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
            replicationAbortSyncTransfer();
            return;
        }
        server.repl_transfer_left = strtol(buf+1,NULL,10);
        redisLog(REDIS_NOTICE,
            "MASTER <-> SLAVE sync: receiving %ld bytes from master",
            server.repl_transfer_left);
        return;
    }

    /* Read bulk data */
    readlen = (server.repl_transfer_left < (signed)sizeof(buf)) ?
        server.repl_transfer_left : (signed)sizeof(buf);
    nread = read(fd,buf,readlen);
