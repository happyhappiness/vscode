        server.master->authenticated = 1;
        server.replstate = REDIS_REPL_CONNECTED;
        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
        /* Rewrite the AOF file now that the dataset changed. */
        if (server.appendonly) rewriteAppendOnlyFileBackground();
    }

    return;

error:
    replicationAbortSyncTransfer();
    return;
}

void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[1024], tmpfile[256];
    int dfd, maxtries = 5;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
    REDIS_NOTUSED(mask);

    redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
    /* This event should only be triggered once since it is used to have a
     * non-blocking connect(2) to the master. It has been triggered when this
     * function is called, so we can delete it. */
    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);

    /* AUTH with the master if required. */
    if(server.masterauth) {
        char authcmd[1024];
        size_t authlen;

        authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
        if (syncWrite(fd,authcmd,authlen,server.repl_syncio_timeout) == -1) {
            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                strerror(errno));
            goto error;
        }
        /* Read the AUTH result.  */
        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout) == -1) {
            redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
                strerror(errno));
            goto error;
        }
        if (buf[0] != '+') {
            redisLog(REDIS_WARNING,"Cannot AUTH to MASTER, is the masterauth password correct?");
            goto error;
        }
    }

    /* Issue the SYNC command */
    if (syncWrite(fd,"SYNC \r\n",7,server.repl_syncio_timeout) == -1) {
        redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
            strerror(errno));
        goto error;
    }

    /* Prepare a suitable temp file for bulk transfer */
