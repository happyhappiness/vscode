    }
}

void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[1024], tmpfile[256];
    int dfd, maxtries = 5;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
    REDIS_NOTUSED(mask);

    /* Remove this event before anything else. */
    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);

    /* AUTH with the master if required. */
    if(server.masterauth) {
        char authcmd[1024];
        size_t authlen;

        authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
        if (syncWrite(fd,authcmd,authlen,5) == -1) {
            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                strerror(errno));
            goto error;
        }
        /* Read the AUTH result.  */
        if (syncReadLine(fd,buf,1024,3600) == -1) {
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
    if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
        redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
            strerror(errno));
        goto error;
    }

    /* Prepare a suitable temp file for bulk transfer */
