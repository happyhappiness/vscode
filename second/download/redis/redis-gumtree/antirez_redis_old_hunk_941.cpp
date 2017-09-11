    char buf[4096];
    ssize_t nread, readlen;
    off_t left;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
    REDIS_NOTUSED(mask);

    /* Static vars used to hold the EOF mark, and the last bytes received
     * form the server: when they match, we reached the end of the transfer. */
    static char eofmark[REDIS_RUN_ID_SIZE];
    static char lastbytes[REDIS_RUN_ID_SIZE];
    static int usemark = 0;

    /* If repl_transfer_size == -1 we still have to read the bulk length
     * from the master reply. */
    if (server.repl_transfer_size == -1) {
        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
            serverLog(REDIS_WARNING,
                "I/O error reading bulk count from MASTER: %s",
                strerror(errno));
            goto error;
        }

        if (buf[0] == '-') {
            serverLog(REDIS_WARNING,
                "MASTER aborted replication with an error: %s",
                buf+1);
            goto error;
