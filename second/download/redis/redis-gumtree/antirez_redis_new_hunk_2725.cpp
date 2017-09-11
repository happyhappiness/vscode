        if (server.sofd > 0) close(server.sofd);
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
            exitFromChild(0);
        } else {
            exitFromChild(1);
        }
    } else {
        /* Parent */
