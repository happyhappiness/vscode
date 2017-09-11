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
