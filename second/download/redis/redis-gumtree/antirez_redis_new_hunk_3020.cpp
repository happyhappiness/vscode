    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
        server.appendonly = 0;
        close(server.appendfd);
        redisLog(REDIS_WARNING,"User tried turning on AOF with CONFIG SET but I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
        return REDIS_ERR;
    }
    return REDIS_OK;
