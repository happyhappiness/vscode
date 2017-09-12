 * as a fully non-blocking VM.
 */

/* Called when the user switches from "appendonly yes" to "appendonly no"
 * at runtime using the CONFIG command. */
static void stopAppendOnly(void) {
    flushAppendOnlyFile();
    fsync(server.appendfd);
    close(server.appendfd);

    server.appendfd = -1;
    server.appendseldb = -1;
    server.appendonly = 0;
    /* rewrite operation in progress? kill it, wait child exit */
    if (server.bgsavechildpid != -1) {
        int statloc;

        if (kill(server.bgsavechildpid,SIGKILL) != -1)
            wait3(&statloc,0,NULL);
        /* reset the buffer accumulating changes while the child saves */
        sdsfree(server.bgrewritebuf);
        server.bgrewritebuf = sdsempty();
        server.bgsavechildpid = -1;
    }
}

/* Called when the user switches from "appendonly no" to "appendonly yes"
 * at runtime using the CONFIG command. */
static int startAppendOnly(void) {
    server.appendonly = 1;
    server.lastfsync = time(NULL);
    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
    if (server.appendfd == -1) {
        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
        return REDIS_ERR;
    }
    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
        server.appendonly = 0;
        close(server.appendfd);
        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
        return REDIS_ERR;
    }
    return REDIS_OK;
}

/* =================== Virtual Memory - Blocking Side  ====================== */

static void vmInit(void) {
