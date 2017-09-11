    return;
}

/* Send a synchronous command to the master. Used to send AUTH and
 * REPLCONF commadns before starting the replication with SYNC.
 *
 * On success NULL is returned.
 * On error an sds string describing the error is returned.
 */
char *sendSynchronousCommand(int fd, ...) {
    va_list ap;
    sds cmd = sdsempty();
    char *arg, buf[256];

    /* Create the command to send to the master, we use simple inline
     * protocol for simplicity as currently we only send simple strings. */
    va_start(ap,fd);
    while(1) {
        arg = va_arg(ap, char*);
        if (arg == NULL) break;

        if (sdslen(cmd) != 0) cmd = sdscatlen(cmd," ",1);
        cmd = sdscat(cmd,arg);
    }
    cmd = sdscatlen(cmd,"\r\n",2);

    /* Transfer command to the server. */
    if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000) == -1) {
        sdsfree(cmd);
        return sdscatprintf(sdsempty(),"Writing to master: %s",
                strerror(errno));
    }
    sdsfree(cmd);

    /* Read the reply from the server. */
    if (syncReadLine(fd,buf,sizeof(buf),server.repl_syncio_timeout*1000) == -1)
    {
        return sdscatprintf(sdsempty(),"Reading from master: %s",
                strerror(errno));
    }

    /* Check for errors from the server. */
    if (buf[0] != '+') {
        return sdscatprintf(sdsempty(),"Error from master: %s", buf);
    }

    return NULL; /* No errors. */
}

void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
    char tmpfile[256], *err;
    int dfd, maxtries = 5;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(privdata);
