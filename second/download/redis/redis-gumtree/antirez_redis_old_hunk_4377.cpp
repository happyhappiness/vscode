    char **messages = NULL;
    int i, trace_size = 0;
    unsigned long offset=0;
    time_t uptime = time(NULL)-server.stat_starttime;
    ucontext_t *uc = (ucontext_t*) secret;
    REDIS_NOTUSED(info);

    redisLog(REDIS_WARNING,
        "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
    redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
        "redis_version:%s; "
        "uptime_in_seconds:%d; "
        "connected_clients:%d; "
        "connected_slaves:%d; "
        "used_memory:%zu; "
        "changes_since_last_save:%lld; "
        "bgsave_in_progress:%d; "
        "last_save_time:%d; "
        "total_connections_received:%lld; "
        "total_commands_processed:%lld; "
        "role:%s;"
        ,REDIS_VERSION,
        uptime,
        listLength(server.clients)-listLength(server.slaves),
        listLength(server.slaves),
        server.usedmemory,
        server.dirty,
        server.bgsavechildpid != -1,
        server.lastsave,
        server.stat_numconnections,
        server.stat_numcommands,
        server.masterhost == NULL ? "master" : "slave"
    ));
    
    trace_size = backtrace(trace, 100);
    /* overwrite sigaction with caller's address */
