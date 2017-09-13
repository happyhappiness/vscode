static int rdbSaveBackground(char *filename) {
    pid_t childpid;

    if (server.bgsaveinprogress) return REDIS_ERR;
    if ((childpid = fork()) == 0) {
        /* Child */
        close(server.fd);
        if (rdbSave(filename) == REDIS_OK) {
            exit(0);
        } else {
            exit(1);
        }
    } else {
        /* Parent */
        redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
        server.bgsaveinprogress = 1;
        return REDIS_OK;
    }
    return REDIS_OK; /* unreached */
}