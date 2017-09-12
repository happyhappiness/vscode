    server.stat_numconnections = 0;
    server.stat_starttime = time(NULL);
    aeCreateTimeEvent(server.el, 1000, serverCron, NULL, NULL);

    if (server.appendonly) {
        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT);
        if (server.appendfd == -1) {
            redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
                strerror(errno));
            exit(1);
        }
    }
}

/* Empty the whole database */
