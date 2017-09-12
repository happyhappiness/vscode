    server.stat_numconnections = 0;
    server.stat_starttime = time(NULL);
    aeCreateTimeEvent(server.el, 1000, serverCron, NULL, NULL);
}

/* Empty the whole database */
