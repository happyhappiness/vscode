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
    if (nread <= 0) {
        redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
            (nread == -1) ? strerror(errno) : "connection lost");
        replicationAbortSyncTransfer();
        return;
    }
    server.repl_transfer_lastio = time(NULL);
    if (write(server.repl_transfer_fd,buf,nread) != nread) {
        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
        replicationAbortSyncTransfer();
        return;
    }
    server.repl_transfer_left -= nread;
    /* Check if the transfer is now complete */
    if (server.repl_transfer_left == 0) {
        if (rename(server.repl_transfer_tmpfile,server.dbfilename) == -1) {
            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
            replicationAbortSyncTransfer();
            return;
        }
        emptyDb();
        if (rdbLoad(server.dbfilename) != REDIS_OK) {
            redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            replicationAbortSyncTransfer();
            return;
        }
        /* Final setup of the connected slave <- master link */
        aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
        zfree(server.repl_transfer_tmpfile);
        close(server.repl_transfer_fd);
        server.master = createClient(server.repl_transfer_s);
        server.master->flags |= REDIS_MASTER;
        server.master->authenticated = 1;
        server.replstate = REDIS_REPL_CONNECTED;
        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
    }
}