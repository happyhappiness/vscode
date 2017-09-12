    }
}

/* ----------------------------------- SLAVE -------------------------------- */

/* Abort the async download of the bulk dataset while SYNC-ing with master */
void replicationAbortSyncTransfer(void) {
    redisAssert(server.replstate == REDIS_REPL_TRANSFER);

    aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
    close(server.repl_transfer_s);
    close(server.repl_transfer_fd);
    unlink(server.repl_transfer_tmpfile);
    zfree(server.repl_transfer_tmpfile);
    server.replstate = REDIS_REPL_CONNECT;
}

/* Asynchronously read the SYNC payload we receive from a master */
void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
    unsigned char buf[4096]
    size_t nread, readlen;

    readlen = (server.repl_transfer_left < sizeof(buf)) ?
        server.repl_transfer_left : sizeof(buf);
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
    }
}

int syncWithMaster(void) {
    char buf[1024], tmpfile[256], authcmd[1024];
    off_t dumpsize;
    int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
    int dfd, maxtries = 5;

