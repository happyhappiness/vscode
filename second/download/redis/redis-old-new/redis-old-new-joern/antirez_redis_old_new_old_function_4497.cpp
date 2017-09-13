static void infoCommand(redisClient *c) {
    sds info;
    time_t uptime = time(NULL)-server.stat_starttime;
    
    info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "connected_clients:%d\r\n"
        "connected_slaves:%d\r\n"
        "used_memory:%d\r\n"
        "changes_since_last_save:%lld\r\n"
        "last_save_time:%d\r\n"
        "total_connections_received:%lld\r\n"
        "total_commands_processed:%lld\r\n"
        "uptime_in_seconds:%d\r\n"
        "uptime_in_days:%d\r\n"
        ,REDIS_VERSION,
        listLength(server.clients)-listLength(server.slaves),
        listLength(server.slaves),
        server.usedmemory,
        server.dirty,
        server.lastsave,
        server.stat_numconnections,
        server.stat_numcommands,
        uptime,
        uptime/(3600*24)
    );
    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}