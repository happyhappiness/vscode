        server.stat_numcommands = 0;
        server.stat_numconnections = 0;
        server.stat_expiredkeys = 0;
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else {
        addReplyError(c,
