static int rewriteAppendOnlyFileBackground(void) {
    pid_t childpid;

    if (server.bgrewritechildpid != -1) return REDIS_ERR;
    if ((childpid = fork()) == 0) {
        /* Child */
        char tmpfile[256];
        close(server.fd);

        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
            exit(0);
        } else {
            exit(1);
        }
    } else {
        /* Parent */
        if (childpid == -1) {
            redisLog(REDIS_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));
            return REDIS_ERR;
        }
        redisLog(REDIS_NOTICE,
            "Background append only file rewriting started by pid %d",childpid);
        server.bgrewritechildpid = childpid;
        return REDIS_OK;
    }
    return REDIS_OK; /* unreached */
}