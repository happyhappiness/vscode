 */
int rewriteAppendOnlyFileBackground(void) {
    pid_t childpid;

    if (server.bgrewritechildpid != -1) return REDIS_ERR;
    if (server.ds_enabled != 0) {
        redisLog(REDIS_WARNING,"BGREWRITEAOF called with diskstore enabled: AOF is not supported when diskstore is enabled. Operation not performed.");
        return REDIS_ERR;
    }
    if ((childpid = fork()) == 0) {
        /* Child */
        char tmpfile[256];

        if (server.ipfd > 0) close(server.ipfd);
        if (server.sofd > 0) close(server.sofd);
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
