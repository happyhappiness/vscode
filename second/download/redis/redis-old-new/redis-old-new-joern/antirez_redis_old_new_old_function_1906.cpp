void configCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc != 4) goto badarity;
        configSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
        if (c->argc != 3) goto badarity;
        configGetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"resetstat")) {
        if (c->argc != 2) goto badarity;
        server.stat_keyspace_hits = 0;
        server.stat_keyspace_misses = 0;
        server.stat_numcommands = 0;
        server.stat_numconnections = 0;
        server.stat_expiredkeys = 0;
        server.stat_rejected_conn = 0;
        server.stat_fork_time = 0;
        server.aof_delayed_fsync = 0;
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"rewrite")) {
        if (c->argc != 2) goto badarity;
        if (server.configfile == NULL) {
            addReplyError(c,"The server is running without a config file");
            return;
        }
        if (rewriteConfig(server.configfile) == -1) {
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c,
            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
    }
    return;

badarity:
    addReplyErrorFormat(c,"Wrong number of arguments for CONFIG %s",
        (char*) c->argv[1]->ptr);
}