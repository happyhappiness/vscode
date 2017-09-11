void stopAppendOnly(void) {
    redisAssert(server.aof_state != REDIS_AOF_OFF);
    flushAppendOnlyFile(1);
    aof_fsync(server.appendfd);
    close(server.appendfd);

    server.appendfd = -1;
    server.appendseldb = -1;
    server.aof_state = REDIS_AOF_OFF;
    /* rewrite operation in progress? kill it, wait child exit */
    if (server.bgrewritechildpid != -1) {
        int statloc;

        if (kill(server.bgrewritechildpid,SIGKILL) != -1)
            wait3(&statloc,0,NULL);
        /* reset the buffer accumulating changes while the child saves */
        sdsfree(server.bgrewritebuf);
        server.bgrewritebuf = sdsempty();
        aofRemoveTempFile(server.bgrewritechildpid);
        server.bgrewritechildpid = -1;
    }
}

/* Called when the user switches from "appendonly no" to "appendonly yes"
 * at runtime using the CONFIG command. */
int startAppendOnly(void) {
    server.lastfsync = time(NULL);
    server.appendfd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
    redisAssert(server.aof_state == REDIS_AOF_OFF);
    if (server.appendfd == -1) {
        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
        return REDIS_ERR;
    }
    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
        close(server.appendfd);
        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
        return REDIS_ERR;
    }
