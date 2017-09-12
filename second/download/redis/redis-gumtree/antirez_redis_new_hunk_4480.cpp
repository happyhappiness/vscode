static void infoCommand(redisClient *c) {
    sds info;
    time_t uptime = time(NULL)-server.stat_starttime;
    int j;
    
    info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
