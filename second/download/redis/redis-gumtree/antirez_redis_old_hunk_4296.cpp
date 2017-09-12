    pid_t childpid;

    if (server.bgrewritechildpid != -1) return REDIS_ERR;
    if (server.vm_enabled) waitZeroActiveThreads();
    if ((childpid = fork()) == 0) {
        /* Child */
        char tmpfile[256];
        close(server.fd);

        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
            exit(0);
