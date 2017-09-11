    /* If repl_transfer_left == -1 we still have to read the bulk length
     * from the master reply. */
    if (server.repl_transfer_left == -1) {
        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
            redisLog(REDIS_WARNING,
                "I/O error reading bulk count from MASTER: %s",
                strerror(errno));
