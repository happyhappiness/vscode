int startAppendOnly(void) {
    server.lastfsync = time(NULL);
    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
    redisAssert(server.aof_state == REDIS_AOF_OFF);
    if (server.appendfd == -1) {
        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
        return REDIS_ERR;
