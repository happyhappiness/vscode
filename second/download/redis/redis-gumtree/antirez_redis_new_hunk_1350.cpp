
    nread = read(fd,buf,readlen);
    if (nread <= 0) {
        serverLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
            (nread == -1) ? strerror(errno) : "connection lost");
        replicationAbortSyncTransfer();
        return;
